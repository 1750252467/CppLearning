#include "unixHeader.h"
#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>
#include <workflow/MySQLUtil.h>
#include <workflow/MySQLResult.h>
#include "Hash.h"
#include "Crypt.h"
#include "Token.h"
#include "OSSInfo.h"
#include <nlohmann/json.hpp>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
using namespace AlibabaCloud::OSS;
using namespace AmqpClient;
using Json = nlohmann::json;
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum){
    printf("wait group done!\n");
    waitGroup.done();
}
int main(){
    signal(SIGINT,sighandler);
    //创建一个服务端对象
    wfrest::HttpServer server;
    InitializeSdk();
    MQConfig mqconfig;
    server.GET("/file/upload",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/view/index.html");
    });
    server.POST("/file/upload",[&mqconfig](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
        //解析请求
        auto userInfo = req->query_list();
        std::string username = userInfo["username"];
        //校验token
        using Form = std::map<std::string,std::pair<std::string,std::string>>;
        Form formdata = req->form();//解析form-data类型的报文请求
        // for(auto &kv:formdata){
        //     fprintf(stderr,"first = %s, second.first = %s, second.second = %s\n",
        //                    kv.first.c_str(),kv.second.first.c_str(),kv.second.second.c_str());
        // }
        // second.first 文件名
        // second.second 文件内容
        // 保存文件
        std::string filename = formdata["file"].first;
        std::string filecontent = formdata["file"].second;
        std::string filepath = "./tmp/" + filename;
        int fd = open(filepath.c_str(),O_RDWR|O_CREAT,0666);
        write(fd,filecontent.c_str(),filecontent.size());
        close(fd);
        Hash hash(filepath);
        std::string filehash = hash.sha1();
        std::string filesizeStr = std::to_string(filecontent.size());

        // //OSS客户端
        // OSSInfo info;
        // ClientConfiguration conf;
        // OssClient client(info.EndPoint,info.AccessKeyID,info.AccessKeySecret,conf);
        // std::string OSSPath = "oss/" + filehash;
        // auto outcome = client.PutObject(info.Bucket,OSSPath,filepath);
        // if(outcome.isSuccess() == false){
        // fprintf(stderr,"Fail, code = %s, msg = %s, requestID = %s\n", 
        //         outcome.error().Code().c_str(), 
        //         outcome.error().Message().c_str(),
        //         outcome.error().RequestId().c_str());
        // }

        if(mqconfig.CurrentStoreType == storeType::OSS){
            if(mqconfig.isAsyncTransferEnable == false){
                //使用OSS备份，但是不启用异步转移
                //OSS客户端
                OSSInfo info;
                ClientConfiguration conf;
                OssClient client(info.EndPoint,info.AccessKeyID,info.AccessKeySecret,conf);
                std::string OSSPath = "oss/" + filehash;
                auto outcome = client.PutObject(info.Bucket,OSSPath,filepath);
                if(outcome.isSuccess() == false){
                fprintf(stderr,"Fail, code = %s, msg = %s, requestID = %s\n", 
                        outcome.error().Code().c_str(), 
                        outcome.error().Message().c_str(),
                        outcome.error().RequestId().c_str());
                }
            }
            else {
                //使用OSS备份，并且启用异步转移
                // 消息队列的生产者
                Channel::ptr_t channel = Channel::Create();
                // 文件名、路径和哈希
                Json fileJson;
                fileJson["filehash"] = filehash;
                fileJson["filename"] = filename;
                fileJson["filepath"] = filepath;
                BasicMessage::ptr_t message = BasicMessage::Create(fileJson.dump());
                channel->BasicPublish(mqconfig.transExchange,mqconfig.transRoutingKey,message);

            }
        }
        // 创建mysql任务
        auto mysqlTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,[resp](WFMySQLTask *mysqlTask){
            if(mysqlTask->get_state() != WFT_STATE_SUCCESS){
                //只能检查权限和连接错误
                fprintf(stderr,"error msg:%s\n",WFGlobal::get_error_string(mysqlTask->get_state(),mysqlTask->get_error()));
                resp->set_status_code("500");
                return;
            }
            // 从mysql任务的响应中获取语法错误
            auto respMysql = mysqlTask->get_resp();
            if(respMysql->get_packet_type() == MYSQL_PACKET_ERROR){
                fprintf(stderr,"error_code = %d, msg = %s\n",respMysql->get_error_code(),respMysql->get_error_msg().c_str());
                resp->set_status_code("500");
                return;
            }
            protocol::MySQLResultCursor cursor(respMysql);
            if(cursor.get_affected_rows() == 1){
                // 重定向
                resp->set_status_code("302");
                resp->headers["Location"] = "/file/upload/success";
                return;
            }
            else{
                resp->set_status_code("500");
                return;
            }
        });
        // 设置任务的属性
        std::string sql = "INSERT INTO clouddisk.tbl_file (file_sha1,file_name,file_size,file_addr,status) VALUES(";
        sql += "'" + filehash + "','" + filename + "'," + filesizeStr + ",'" + filepath + "', 0);";
        sql += "INSERT IGNORE INTO clouddisk.tbl_user_file (user_name,file_sha1,file_name,file_size,status) VALUES('"
               + username + "','"+filehash+"','"+filename + "'," + filesizeStr + ", 0);";
        fprintf(stderr,"sql = %s\n", sql.c_str());
        mysqlTask->get_req()->set_query(sql);
        // 把任务加入到序列中
        series->push_back(mysqlTask);   
    });
    server.GET("/file/upload/success",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->String("upload success!");
    });
    server.GET("/file/download",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        // 下载方案1
        // auto fileInfo = req->query_list();
        // // filehash filename filesize
        // std::string filehash = fileInfo["filehash"];
        // std::string filename = fileInfo["filename"];
        // std::string filesizeStr = fileInfo["filesize"];
        // int filesize= std::stoi(filesizeStr);
        // // 打开文件，写入响应体
        // std::string filepath = "./tmp/" + filename;
        // int fd = open(filepath.c_str(),O_RDONLY);
        // char *buf = new char[filesize];
        // read(fd,buf,filesize);
        // resp->append_output_body(buf,filesize);
        // // 浏览器的行为是下载
        // resp->headers["Content-Type"] = "application/octet-stream";
        // resp->headers["content-disposition"] = "attachment;filename="+filename;
        // delete []buf;

        //下载方案2
        //生成一个文件在nginx中的url
        //返回重定向给前端
        auto fileInfo = req->query_list();
        std::string filename = fileInfo["filename"];
        resp->headers["Location"] = "http://192.168.128.140:1235/" + filename;
        resp->set_status_code("302");
    });
    
    server.GET("/user/signup",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/view/signup.html");
    });
    server.POST("/user/signup",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
        //urlencoded
        auto formMap = req->form_kv();
        std::string username = formMap["username"];
        std::string password = formMap["password"];
        // 加密密码
        std::string salt = "12345678";
        Crypt crypt(password,salt);
        // 创建mysql任务
        auto mysqlTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,[resp](WFMySQLTask *mysqlTask){
            if(mysqlTask->get_state() != WFT_STATE_SUCCESS){
                //只能检查权限和连接错误
                fprintf(stderr,"error msg:%s\n",WFGlobal::get_error_string(mysqlTask->get_state(),mysqlTask->get_error()));
                resp->set_status_code("500");
                return;
            }
            // 从mysql任务的响应中获取语法错误
            auto respMysql = mysqlTask->get_resp();
            if(respMysql->get_packet_type() == MYSQL_PACKET_ERROR){
                fprintf(stderr,"error_code = %d, msg = %s\n",respMysql->get_error_code(),respMysql->get_error_msg().c_str());
                resp->String("FAIL");
                return;
            }
            protocol::MySQLResultCursor cursor(respMysql);
            if(cursor.get_affected_rows() == 1){
                resp->String("SUCCESS");
                return;
            }
            else{
                resp->String("FAIL");
                return;
            }
        });            
        // 修改任务属性
        std::string sql = "INSERT INTO clouddisk.tbl_user (user_name,user_pwd,status) VALUES('" 
        + username + "','" + crypt.encoded() + "',0);";
        fprintf(stderr,"sql = %s\n", sql.c_str());
        mysqlTask->get_req()->set_query(sql);
        // 加入到序列中
        series->push_back(mysqlTask);
    });
    server.GET("/static/view/signin.html",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/view/signin.html");
    });
    server.POST("/user/signin",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
        //解析用户请求
        auto formMap = req->form_kv();
        std::string username = formMap["username"];
        std::string password = formMap["password"];
        std::string salt = "12345678";
        
        auto mysqlTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,[username,password,salt,resp](WFMySQLTask *mysqlTask){
            auto respMysql = mysqlTask->get_resp();
            protocol::MySQLResultCursor cursor(respMysql);
            std::vector<std::vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows);
            if(rows[0][0].is_string()){
                std::string resultMysql = rows[0][0].as_string();
                Crypt crypt(password,salt);
                if(crypt.encoded() == resultMysql){
                    //登录成功
                    Token token(username,"abcdefgh");
                    //更新mysql当中的token
                    auto newTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,nullptr);
                    //设置任务的属性
                    std::string sql = "REPLACE INTO clouddisk.tbl_user_token (user_name,user_token) VALUES('" 
                                      + username + "','"+token.getToken()+"');";
                    //fprintf(stderr,"sql = %s\n", sql.c_str());
                    newTask->get_req()->set_query(sql);
                    series_of(mysqlTask)->push_back(newTask);

                    Json respMsg;
                    Json data;
                    data["Token"] = token.getToken();
                    data["Username"] = username;
                    data["Location"] = "/static/view/home.html";
                    respMsg["data"] = data;
                    respMsg["code"] = 0;
                    respMsg["msg"] = "OK";
                    resp->String(respMsg.dump());
                }
                else{
                    //登录失败
                    resp->set_status_code("500");
                    return;
                }
            }
            else{
                //登录失败
                resp->set_status_code("500");
                return;
            }
        });
        std::string sql = "SELECT user_pwd FROM clouddisk.tbl_user WHERE user_name='"+username+"' LIMIT 1;";
        fprintf(stderr,"sql = %s\n", sql.c_str());
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });
    server.GET("/static/view/home.html",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/view/home.html");
    });
    server.GET("/static/js/auth.js",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/js/auth.js");
    });
    server.GET("/static/img/avatar.jpeg",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        resp->File("static/img/avatar.jpeg");
    });
    server.POST("/user/info",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
        //解析请求
        auto userInfo = req->query_list();
        std::string username = userInfo["username"];
        //校验token
        //查询用户信息
        auto mysqlTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,[resp](WFMySQLTask *mysqlTask){
            auto respMysql = mysqlTask->get_resp();
            protocol::MySQLResultCursor cursor(respMysql);
            std::vector<std::vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows);

            Json respMsg;
            Json data;
            data["Username"] = rows[0][0].as_string();
            data["SignupAt"] = rows[0][1].as_datetime();
            respMsg["data"] = data;
            respMsg["code"] = 0;
            respMsg["msg"] = "OK";
            resp->String(respMsg.dump());
        });
        std::string sql = "SELECT user_name,signup_at FROM clouddisk.tbl_user WHERE user_name='"
                          + username + "' LIMIT 1;";
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });
    server.POST("/file/query",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp, SeriesWork *series){
        //解析请求
        auto userInfo = req->query_list();
        std::string username = userInfo["username"];
        //校验token    
        //解析报文体
        auto formKV = req->form_kv();
        std::string limit = formKV["limit"];
        auto mysqlTask = WFTaskFactory::create_mysql_task("mysql://root:a0b0@localhost",0,[resp](WFMySQLTask *mysqlTask){
            auto respMysql = mysqlTask->get_resp();
            protocol::MySQLResultCursor cursor(respMysql);
            std::vector<std::vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows);

            Json arr;
            for(int i = 0; i < rows.size(); ++i){
                Json data;
                data["FileHash"] = rows[i][0].as_string();
                data["FileName"] = rows[i][1].as_string();
                data["FileSize"] = rows[i][2].as_ulonglong();
                data["UploadAt"] = rows[i][3].as_datetime();
                data["LastUpdated"] = rows[i][4].as_datetime();
                arr.push_back(data);
            }
            resp->String(arr.dump());
        });
        std::string sql = "SELECT file_sha1,file_name,file_size,upload_at,last_update FROM clouddisk.tbl_user_file WHERE user_name='"
                          + username + "' LIMIT " + limit +";";
        fprintf(stderr,"sql = %s\n", sql.c_str());
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });
    server.POST("/file/downloadurl",[](const wfrest::HttpReq *req, wfrest::HttpResp *resp){
        auto fileInfo = req->query_list();
        std::string filename = fileInfo["filename"];
        resp->String("http://192.168.128.140:1235/" + filename);
    });
    if(server.track().start(1234) == 0){
        server.list_routes();
        waitGroup.wait();
        server.stop();
        ShutdownSdk();
    }
    else{
        perror("Cannot start server!");
        return -1;
    }
    
    return 0;
}

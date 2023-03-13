/* File Name main.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-10-06 21:29
 * Last Modified 2022-10-08 18:19
 */
#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>
#include "Hash.h"
#include <workflow/MySQLUtil.h>
#include <workflow/MySQLResult.h>
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    printf("wait group done!\n");
    waitGroup.done();
}

int main() {
    signal(SIGINT,sighandler);

    wfrest::HttpServer server;
    server.GET("/file/upload",[](const wfrest::HttpReq *req,wfrest::HttpResp *resp) {
               resp->File("static/view/index.html");
    });
    server.POST("/file/upload",[](const wfrest::HttpReq *req,wfrest::HttpResp *resp,SeriesWork *series) {
        using Form = std::map<std::string,std::pair<std::string,std::string>>;
        Form formdata = req->form();

        std::string filename = formdata["file"].first;
        std::string filecontent = formdata["file"].second;
        std::string filepath = "./tmp/" + filename;
        int fd = open(filepath.c_str(),O_RDWR|O_CREAT,0666);
        write(fd,filecontent.c_str(),filecontent.size());
        close(fd);

        Hash hash(filepath);
        std::string filehash = hash.sha1();
        std::string filesizeStr = std::to_string(filecontent.size());
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
        std::string sql = "INSERT INTO cloudisk.tbl_file (file_sha1,file_name,file_size,file_addr,status) VALUES(";
        sql += "'"+filehash + "','" + filename + "'," + filesizeStr + ",'" + filepath + "',0);";
        
        fprintf(stderr,"sql = %s\n", sql.c_str());
        mysqlTask->get_req()->set_query(sql);
        // 把任务加入到序列中
        series->push_back(mysqlTask);   
        });
        server.GET("/file/upload/success",[](const wfrest::HttpReq *req,wfrest::HttpResp *resp) {
        resp->String("upload success!");
    });
        server.GET("/file/download",[](const wfrest::HttpReq *req,wfrest::HttpResp *resp) {
           // auto fileInfo = req->query_list();

           // std::string filehash = fileInfo["filehash"];
           // std::string filename = fileInfo["filename"];
           // std::string filesizeStr = fileInfo["filesize"];
           // int filesize = std::stoi(filesizeStr);

           // std::string filepath = "./tmp/"+filename;
           // int fd = open(filepath.c_str(),O_RDONLY);
           // char *buf = new char[filesize];
           // read(fd,buf,filesize);
           // resp->append_output_body(buf,filesize);

           // resp->headers["Content-Type"] = "application/octet-stream";
           // resp->headers["content-dispostion"] = "attachment;filename="+filename;
           // delete []buf;
           auto fileInfo = req->query_list();
           std::string filename = fileInfo["filename"];
           resp->headers["Location"] = "http://192.168.128.133:1235/"+filename;
           resp->set_status_code("302");
        });
    if(server.track().start(1234) == 0) {
        server.list_routes();
        waitGroup.wait();
        server.stop();
    }
    else {
        perror("Cannot start server!");
        return -1;
    }

    return 0;
}



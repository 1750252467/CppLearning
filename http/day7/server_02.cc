#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/HttpUtil.h>
#include <nlohmann/json.hpp>
using Json = nlohmann::json;
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum){
    printf("wait group done!\n");
    waitGroup.done();
}
void process(WFHttpTask *serverTask){
    auto req = serverTask->get_req();
    auto resp = serverTask->get_resp();
    std::string uri = req->get_request_uri();
    //fprintf(stderr,"uri = %s\n",uri.c_str());

    std::string path = uri.substr(0,uri.find("?"));
    std::string queryKV = uri.substr(uri.find("?")+1);
    //std::string username = queryKV.substr(queryKV.find("=")+1);
    //fprintf(stderr,"username = %s\n",username.c_str());
    std::string method = req->get_method();
    if(path == "/file/muplload/init" && method == "POST") {

        std::string username = queryKV.substr(queryKV.find("=")+1);
        //fprintf(stderr,"username = %s\n",username.c_str());
        time_t now = time(nullptr);
        struct tm *ptm = localtime(&now);
        char buf[128] = {0};
        sprintf(buf,"%s%02d:%02d",username.c_str(),ptm->tm_hour,ptm->tm_min);
        std::string uploadID = buf;
        fprintf(stderr,"uploadID = %s\n",uploadID.c_str());

        const void *body;
        size_t size;
        req->get_parsed_body(&body,&size);
        Json fileInfo = Json::parse(static_cast<const char *>(body));
        std::string filename = fileInfo["filename"];
        std::string filehash = fileInfo["filehash"];
        int filesize = fileInfo["filesize"];
        fprintf(stderr,"filename = %s\nfilehash = %s\nfilesize = %d\n",filename.c_str(),filehash.c_str(),filesize);
        
        int chunksize = 1024*1024;
        int chunkcount;
        chunkcount = filesize/chunksize + (filesize%chunksize != 0);
        auto redisTask = WFTaskFactory::create_redis_task("redis://localhost",0,nullptr);
        redisTask->get_req()->set_request("HSET",{uploadID,"chunkcount",std::to_string(chunkcount),
                                                           "filehash",filehash,
                                                           "filesize",std::to_string(filesize)});
        series_of(serverTask)->push_back(redisTask);

        Json chunkInfo;
        chunkInfo["status"] = "OK";
        chunkInfo["uploadID"] = uploadID;
        chunkInfo["chunkcount"] = chunkcount;
        chunkInfo["chunksize"] = chunksize;
        chunkInfo["filehash"] = filehash;
        chunkInfo["filesize"] = filesize;
        chunkInfo["filename"] = filename;
        resp->append_output_body(chunkInfo.dump());
    }
    else if("/file/mupload/uppart" && method == "POST") {

        std::string uploadIDKV = queryKV.substr(0,queryKV.find("&"));
        std::string chkidxKV = queryKV.substr(queryKV.find("&")+1);
        std::string uploadID = uploadIDKV.substr(uploadIDKV.find("=")+1);
        std::string chkidx = chkidxKV.substr(chkidxKV.find("=")+1);
        fprintf(stderr,"uploadID = %s\nchkidx = %s\n",uploadID.c_str(),chkidx.c_str());

        mkdir(uploadID.c_str(),0777);

        std::string localpath = uploadID + "/" + chkidx;
        int fd = open(localpath.c_str(),O_RDWR|O_CREAT,0666);

        const void *body;
        size_t size;
        req->get_parsed_body(&body,&size);

        write(fd,body,size);
        close(fd);

        //异步写入
        // auto pwriteTask = WFTaskFactory::create_pwrite_task(fd,body,size,0,[fd](WFFileIOTask *pwriteTask){
        //    close(fd); 
        // });
        // pwriteTask->start();

        auto redisTask = WFTaskFactory::create_redis_task("redis://localhost",0,nullptr);
        redisTask->get_req()->set_request("HSET",{uploadID,"chkidx_"+chkidx,"1"});
        series_of(serverTask)->push_back(redisTask);

        resp->append_output_body("upload part success");


    }
    else if(path == "/file/mupload/complete"&& method == "POST") {
        std::string uploadID = queryKV.substr(queryKV.find("=")+1);
        auto redisTask = WFTaskFactory::create_redis_task("redis://localhost",0,[resp](WFRedisTask *redisTask) {
            auto reqRedis = redisTask->get_req();
            auto respRedis = redisTask->get_resp();
            protocol::RedisValue value;
            respRedis->get_result(value);
            int total = -1;
            int current = 0;
            if(value.is_array()) {
                for(int i = 0; i < value.arr_size(); i += 2) {
                    std::string key = value[i].string_value();
                    std::string val = value[i+1].string_value();
                    if(key == "chunkcount") {
                        total = std::stoi(val);
                    }
                    if(key.substr(0,7) == "chkidx_") {
                        ++current;
                    }
                }
                if(total == -1) {
                    resp->append_output_body("uploadID is not found");
                    return;
                }
                else if(total != current) {
                    resp->append_output_body("upload is not completed");
                    return;
                }
                else {
                    resp->append_output_body("upload is completed");
                    return;
                }
            }
            else {
                resp->append_output_body("upload is completed");
                return;
            }
        });
        redisTask->get_req()->set_request("HGETALL",{uploadID});
        series_of(serverTask)->push_back(redisTask);
    } 
}
int main(){
    signal(SIGINT,sighandler);
    //创建一个服务端对象，总是以一个proces函数对象为参数
    WFHttpServer server(process);
    if(server.start(1234) == 0){//start返回0的时候，说明监听成功
        waitGroup.wait();
        server.stop();//关闭掉服务端
    }
    else{
        perror("Server start fail!\n");
        return -1;
    }
    return 0;
}
/* File Name loginServer.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-09-30 22:42
 * Last Modified 2022-10-01 00:13
 */
#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/HttpUtil.h>

static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    printf("wait group done");
    waitGroup.done();
}

struct SeriesContext {
    std::string password;
    protocol::HttpResponse *resp;
};

void redisCallback(WFRedisTask *redisTask) {
    fprintf(stderr, "redisCallback is running!\n");
    auto req = redisTask->get_req();
    auto resp = redisTask->get_resp();

    int state = redisTask->get_state();
    int error = redisTask->get_error();
    protocol::RedisValue value;
    switch(state) {
    case WFT_STATE_SYS_ERROR:
        fprintf(stderr,"system error: %s\n",strerror(error));
        break;
    case WFT_STATE_DNS_ERROR:
        fprintf(stderr,"dns error: %s\n",gai_strerror(error));
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(value);
        if(value.is_error()) {
            fprintf(stderr,"redis error\n");
            state =WFT_STATE_TASK_ERROR;
        }
        break;
    }
    if(state != WFT_STATE_SUCCESS) {
        fprintf(stderr,"error occur!\n");
        return;
    }
    SeriesContext* context = static_cast<SeriesContext*>(series_of(redisTask)->get_context());

    std::string cmd;
    req->get_command(cmd);
    fprintf(stderr,"redis request, cmd = %s\n",cmd.c_str());

    if(value.is_string()) {
        if(value.string_value() == context->password) {
            context->resp->append_output_body("Login Success");
            return;
        } 
    }
    context->resp->append_output_body("Login Fail");
    return;
}


void process(WFHttpTask* serverTask) {
    auto req = serverTask->get_req();
    auto resp = serverTask->get_resp();
    std::string uri =req->get_request_uri();
    fprintf(stderr, "uri = %s\n",uri.c_str());

    std::string nameKV = uri.substr(0,uri.find("&"));
    std::string passwordKV = uri.substr(uri.find("&")+1);
    fprintf(stderr,"nameKV = %s\n", nameKV.c_str());
    fprintf(stderr,"passwordKV = %s\n",passwordKV.c_str());
    std::string name = nameKV.substr(nameKV.find("=")+1);
    std::string password = passwordKV.substr(passwordKV.find("=")+1);
    fprintf(stderr,"name = %s\n",name.c_str());
    fprintf(stderr,"password = %s\n",password.c_str());

    SeriesContext* context = new SeriesContext;
    series_of(serverTask)->set_context(context);
    context->password = password;
    context->resp = resp;

    auto redisTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",0,redisCallback);

    redisTask->get_req()->set_request("HGET",{"45USER",name});

    series_of(serverTask)->push_back(redisTask);
    serverTask->set_callback([context](WFHttpTask* httpTask) {
                             fprintf(stderr,"callback is running!\n");
                             fprintf(stderr,"context is deleted!\n");
                             delete context;

                             });


}

int main() {
    signal(SIGINT,sighandler);

    WFHttpServer server(process);
    if(server.start(1234) == 0) {
        waitGroup.wait();
        server.stop();
    }
    else {
        perror("Server start fail!\n");
        return -1;
    }
    return 0;
}

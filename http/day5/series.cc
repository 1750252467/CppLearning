/* File Name series.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-09-27 15:34
 * Last Modified 2022-09-27 23:03
 */
#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
#include <workflow/RedisMessage.h>

static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    printf("wait group done!\n");
    waitGroup.done();
}    
void callback(WFRedisTask *redisTask) {
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
        fprintf(stderr,"dns error: %s\n",strerror(error));
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(value);
        if(value.is_error()) {
            fprintf(stderr,"redis error\n");
            state = WFT_STATE_TASK_ERROR;
        }
        break;
    }
    if(state != WFT_STATE_SUCCESS) {
        fprintf(stderr,"redis error\n");
        return;
    }
    
    std::string cmd;
    req->get_command(cmd);
    fprintf(stderr,"redis request,cmd = %s\n",cmd.c_str());
    if(cmd == "GET") {
        int *pi = static_cast<int *>(redisTask->user_data);
        fprintf(stderr,"i = %d\n",*pi);
        delete pi;

        if(value.is_string()) {
            fprintf(stderr,"value is a string,value = %s\n",value.string_value().c_str());
        }else if(value.is_array()) {
            fprintf(stderr,"value is an arry\n");
            for(int i = 0; i < value.arr_size();++i) {
                printf("arr[%d] = %s\n", i, value.arr_at(i).string_value().c_str());
            }
        }
        fprintf(stderr,"second callback is done!\n");
    }
    else {

        int *pi = new int(123);
        auto nextTask = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",0,callback);
        nextTask->get_req()->set_request("GET",{"45KEY"});
        nextTask->user_data = static_cast<void*>(pi);

        auto series = series_of(redisTask);
        series->push_back(nextTask);

        fprintf(stderr,"first callback is done!\n");
    }

}
int main() {
    signal(SIGINT,sighandler);

    auto redisTask1 = WFTaskFactory::create_redis_task("redis://127.0.0.1:6379",0,callback);

    auto req =redisTask1->get_req();
    req->set_request("SET",{"45KEY","2"});

    redisTask1->start();
    waitGroup.wait();
    return 0;
}




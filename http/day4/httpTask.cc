#include "linuxHeader.h"
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
static WFFacilities::WaitGroup waitGroup(1);
void sighandler(int signum) {
    printf("wait group done!\n");
    waitGroup.done();
}
void callback(WFHttpTask *httpTask) {
    auto rep = httpTask->get_req();
    auto resp = httpTask->get_resp();

    int state = httpTask->get_state();
    int error = httpTask->get_error();
    switch(state) {
    case WFT_STATE_SYS_ERROR:    
        fprintf(stderr,"system error: %s\n",strerror(error));
        break;
    case WFT_STATE_DNS_ERROR:
        fprintf(stderr,"dns error: %s\n",gai_strerror(error));
        break;
    case WFT_STATE_SUCCESS:
        break;

    }
    if(state != WFT_STATE_SUCCESS) {
        fprintf(stderr,"error occur!\n");
        return;
    }

    fprintf(stderr, "request\r\n%s %s %s\r\n",rep->get_method(),
                                              rep->get_request_uri(),
                                              rep->get_http_version());
    protocol::HttpHeaderCursor cursor(rep);
    std::string name;
    std::string value;
    while(cursor.next(name,value)) {
        fprintf(stderr,"%s:%s\r\n",name.c_str(),value.c_str());
    }
    fprintf(stderr,"\r\n");

    fprintf(stderr,"response\r\n%s %s %s\r\n",resp->get_http_version(),
                                              resp->get_status_code(),
                                              resp->get_reason_phrase());
    

}


int main() {
    signal(SIGINT,sighandler);

    auto httpTask = WFTaskFactory::create_http_task("http://192.168.128.132",0,0,callback);

    auto rep = httpTask->get_rep();

    rep->add_header_pair("key1","vall");

    httpTask->start();
    waitGroup.wait();
    return 0;
}
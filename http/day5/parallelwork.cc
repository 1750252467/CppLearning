/* File Name parallelwork.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-09-27 23:05
 * Last Modified 2022-09-28 09:07
 */
#include "linuxHeader.h"
#include <workflow/WFFacilities.h>

static WFFacilities::WaitGroup waitGroup(1);

void sighandler(int signum) {
    printf("wait group done!\n");
    waitGroup.done();
} 
struct SeriesContext {
    std::string url;
    int state;
    int error;
    protocol::HttpResponse resp;
};

void parallelCallback(const ParallelWork *pwork) {
    
    for(int i = 0; i < pwork->size(); ++i) {
        SeriesContext *context = static_cast<SeriesContext*>(pwork->series_at(i)->get_context());
        fprintf(stderr, "--------------------------------\n");
        fprintf(stderr,"url = %s\n",context->url.c_str());
        if(context->state == WFT_STATE_SUCCESS) {
            const void *body;
            size_t size;

        }
        else {
            fprintf(stderr,"Error, state = %d, error = %d\n",context->state,context->error);

        }
        delete context;
    } 
}

void httpCallback(WFHttpTask* httpTask) {

    SeriesContext* context = static_cast<SeriesContext*>(series_of(httpTask)->get_context());
    context->state = httpTask->get_state();
    context->error = httpTask->get_error();
    context->resp = std::move(*httpTask->get_resp());
}

int main() {
    signal(SIGINT,sighandler);

    auto pwork = Workflow::create_parallel_work(parallelCallback);
    std::vector<std::string> vec = {"http://www.google.com","http://47.94.147.94","http://localhost:8080"};
    for(int i = 0; i < vec.size(); ++i) {
        
        auto httpTask = WFTaskFactory::create_http_task(vec[i],0,0,httpCallback);
        auto req  = httpTask->get_req();
        req->add_header_pair("Accept","*/*");
        req->add_header_pair("User-Agent","myhttpclient");
        
        auto series = Workflow::create_series_work(httpTask,nullptr);
        SeriesContext *context = new SeriesContext;
        series->set_context(context);
        context->url = vec[i];
        pwork->add_series(series);
    }
    Workflow::start_series_work(pwork,nullptr);
    waitGroup.wait();
    return 0;


}



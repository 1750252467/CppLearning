#include <func.h>

int main(){
    //阻塞2号信号
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    int ret = sigprocmask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("block sucess!\n");
    //睡眠5秒
    sleep(5);
    //检测是否有信号挂起
    sigset_t pend;
    sigemptyset(&pend);
    sigpending(&pend);
    if(sigismember(&pend,SIGINT)){
        printf("SIGINT is pending!\n");
    }else{
        printf("SIGINT is not pending!\n");
    }
    //解除阻塞
    ret = sigprocmask(SIG_UNBLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");

    while(1);

    return 0;
}

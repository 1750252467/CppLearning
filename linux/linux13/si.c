#include <func.h>

void sigfunc(int signum, siginfo_t *p,void *p1){

    printf("before %d is coming\n",signum);
    sleep(3);

    sigset_t pendingSet;
    sigpending(&pendingSet);
    //捕获3号是否有未决状态
    if(sigismember(&pendingSet,SIGQUIT)){
        printf("SIGQUIT is pending!\n");
    }
    else{
        printf("SIGQUIT is not pending!\n");
    }
    //打印3号是否产生过
    printf("after %d is coming\n",signum);
}
int main(void){

    struct sigaction act;
    memset(&act,0,sizeof(act));

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigfunc;
    //屏蔽临时阻塞3号信号
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    //注册2号信号
    int ret = sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret, -1,"sigaction");
    //注册3号信号
    ret = sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");

    while(1);

    return 0;
}

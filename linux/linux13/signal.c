#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1){
    printf("%d is coming\n",signum);

} 
int main(){
    
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_flags = SA_SIGINFO|SA_RESTART;
    act.sa_sigaction = sigfunc;
    int ret = sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    char buf[128] ={0};
    ret = read(STDIN_FILENO,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    return 0;
}


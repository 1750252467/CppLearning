#include <func.h>

sighandler_t signal_restart(int signo,sighandler_t handler){
    struct sigaction act,oldact;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    //
    act.sa_flags = 0;

    act.sa_flags |= SA_RESTART;

    int retval = sigaction(signo,&act,&oldact);
    if(retval ==-1){
        return SIG_ERR;

    }
}
sighandler_t signal_interrupt(int signo, sighandler_t handler){
    struct sigaction act,oldact;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);

    act.sa_flags = 0;

    #ifdef SA_INTeRRUPT
        act.sa_flags |= SA_INTERRUpT;
    #endif

    int retval = sigaction(signo,&act,&oldact);
    if(retval == -1){
        return SIG_ERR;
    }
    return oldact.sa_handler;
}

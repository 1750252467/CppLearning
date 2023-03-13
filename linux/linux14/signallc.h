#ifndef __signallc_H__
#define __signallc_H__

#include <func.h>

sighandler_t signal_restart(int signo,sighandler_t handler){
    struct sigaction act,oldact;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    //
    act.sa_flags = 0;

    act.sa_flags |= SA_RESTART;//SA_RESTART 让低速系统调用可以自动重启

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

    #ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;//
    #endif

    int retval = sigaction(signo,&act,&oldact);
    if(retval == -1){
        return SIG_ERR;
    }
    return oldact.sa_handler;
}





#endif

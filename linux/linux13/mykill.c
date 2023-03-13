#include <func.h>
int main(int argc,char *argv[]){

    ARGS_GHECK(argc,3);
    int sig = atoi(argv[1]+1);
    pid_t pid = atoi(argv[2]);

    int ret = kill(pid,sig);
    ERROR_CHECK(ret,-1,"kill");
    return 0;
}

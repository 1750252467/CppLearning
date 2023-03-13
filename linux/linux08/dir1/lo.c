#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<func.h>
int main(int argc,char *argv[]){
    ARGS_GHECK(argc,3);
    int oldfd1 = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0666);
    ERROR_CHECK(oldfd1,-1,"open");
    
    int newfd1 = dup2(oldfd1,STDOUT_FILENO );
    ERROR_CHECK(newfd1,-1,"dup2");
    
    printf("newfd1 = %d\n",newfd1);
    
    int oldfd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0666);
    ERROR_CHECK(oldfd2,-1,"open");
    
    int newfd2 = dup2(oldfd2,STDERR_FILENO);
    ERROR_CHECK(newfd2,-1,"dup2");
    
    perror("dup2");
    return 0;
}

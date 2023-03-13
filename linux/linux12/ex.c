#include <func.h>

int main(void){

    pid_t pid = fork();
    if(pid == 0){
        printf("I am child\n");
        execl("./rand","rand","15","65",(char *)0);
        printf("you can not see me!\n");

    }else{
         printf("I am parent\n");
         printf("you can see me!\n");
         sleep(1);
    }
    return 0;
}

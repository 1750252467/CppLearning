#include <func.h>

int main(int argc, char *argv[]){
    int a = 0x12345678;
    printf("a:%x\n",a);
    printf("a:%d\n",a);

    char *p = (char*)&a;
    printf("*p:%x\n",*p);
    return 0;
}

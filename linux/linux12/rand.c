#include <func.h>

int main(int argc,char *argv[]){
    ARGS_GHECK(argc,3);
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    srand((unsigned)time(NULL));
    int ret =a + rand() % (b - a + 1);
    printf("%d\n",ret);
    return 0;
}

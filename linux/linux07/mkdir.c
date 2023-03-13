#include <func.h>
int main(int argc, char* argv[]){
    ARGS_GHECK(argc,2);
    int retval = mkdir(argv[1],0777);
    ERROR_CHECK(retval,-1,"mkdir");
    return 0;
}
    

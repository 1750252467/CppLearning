#include <func.h>

#define LENGTH 4096

int main(int argc, char *argv[]){
    ARGS_GHECK(argc,3);
    
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");

    int fdw = open(argv[2], O_RDWR | O_CREAT |O_TRUNC,0666);
    ERROR_CHECK(fdw,-1,"open");
    
    struct stat statbuf;
    fstat(fdr,&statbuf);

    ftruncate(fdw,statbuf.st_size);
    off_t fsize = 0;
    int cp_size;
     
    while(fsize <  statbuf.st_size){
        if(statbuf.st_size - fsize >= LENGTH){
            cp_size = LENGTH;
        }else{
            cp_size = statbuf.st_size -fsize;
        }
        char *src = (char*)mmap(NULL, cp_size,PROT_READ,MAP_SHARED,fdr,fsize);
        ERROR_CHECK(src,MAP_FAILED,"mmap");

        char *dst = (char*)mmap(NULL,cp_size,PROT_READ | PROT_WRITE,MAP_SHARED,fdw,fsize);
        ERROR_CHECK(dst,MAP_FAILED,"mmap");
         memcpy(dst,src,cp_size);
         munmap(src,cp_size);        
         munmap(dst,cp_size);    
    }
    
    return 0;
}

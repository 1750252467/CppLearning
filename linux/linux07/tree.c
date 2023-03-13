#include <func.h>

int directories = 0,files = 0;

void dfs_print(char *dir, int width);
int main(int argc,char *argv[]){
    ARGS_GHECK(argc,2);
    puts(argv[1]);
    dfs_print(argv[1],4);
    printf("\n");

    printf("%d directories, %d files\n",directories, files);
    return 0;
}

void dfs_print(char *dir,int width){
    DIR *pdir = opendir(dir);
    ERROR_CHECK(pdir,NULL,"opendir");

    struct dirent* pdirent;
    while((pdirent = readdir(pdir)) != NULL){
        if(pdirent->d_name[0] == '.'){
            continue;
        }
        for(int i = 0; i < width; i++){
            printf("|_");
            if(i == width-1){

        for(int i = 0;i < width; i++){
            printf("_");
            
             }
        }
        }
        puts(pdirent->d_name);
        
        if(pdirent->d_type == DT_DIR) {
            directories++;
            char pathname[1024];
            sprintf(pathname,"%s/%s",dir,pdirent->d_name);

            dfs_print(pathname,width+4);
        }else {
            files++;
        }
    }
}


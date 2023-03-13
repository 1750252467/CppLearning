#include <func.h>
typedef struct student {
	int num;
	char name[20];
	int score;
}stu;
int main(int argc,char *argv[]) {
    
	stu s[3] = { {1,"aa",90},{2,"bb",80},{3,"cc",70} };
	ARGS_GHECK(argc,2);

    int fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC ,0666);
    ERROR_CHECK(fd,-1,"open");
   
    for(int i=0;i<3;i++){
        write(fd,s+i,sizeof(stu));
    }
    
    off_t offset =lseek(fd,0,SEEK_SET);
    ERROR_CHECK(offset ,-1,"lseek");

    for(int i=0;i<3;i++){
        read(fd,s+i,sizeof(stu));
        printf("id=%d name=%s score=%d\n",(s+i)->num,(s+i)->name,(s+i)->score);
    }

    close(fd);
    return 0;
}

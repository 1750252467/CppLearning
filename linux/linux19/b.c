#include <func.h>

int main(int argc,char *argv[]){
    struct hostent *p =gethostbyname(argv[1]);
    if(p){
        printf("p->h_name:%s\n",p->h_name);
        for(int i = 0;p->h_aliases[i]!=NULL;++i){
            printf("p->h_aliases[%d]:%s\n",i,p->h_aliases[i]);

        }
        printf("addrtype:%d\n",p->h_addrtype);
        printf("addr length:%d\n",p->h_length);

        char buff[64] = {0};
        for(int i=0;p->h_addr_list[i]!=NULL;i++){
            memset(buff,0,sizeof(buff));
            printf("ip:%s\n",inet_ntop(p->h_addrtype,p->h_addr_list[i],buff,sizeof(buff)));
        }
    }
    return 0;
}

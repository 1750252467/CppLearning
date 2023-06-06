#include "unixHeader.h"
#include "Hash.h"
#include <openssl/sha.h>
Hash::Hash(std::string filename):
    _filename(filename){

    }

std::string Hash::sha1(){
    int fd = open(_filename.c_str(),O_RDONLY);
    char buf[4096];
    // Init
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    // Update
    while(true){
        bzero(buf,sizeof(buf));
        int ret = read(fd,buf,sizeof(buf));
        if(ret == 0){
            break;
        }
        SHA1_Update(&ctx,buf,ret);
    }
    // Final
    unsigned char md[20];
    SHA1_Final(md,&ctx);
    char frag[3];
    std::string sha1Res;
    for(int i = 0; i < 20; ++i){
        sprintf(frag,"%02x",md[i]);//把一个字节弄成2位16进制数
        sha1Res = sha1Res + frag;
    }
    return sha1Res;
}
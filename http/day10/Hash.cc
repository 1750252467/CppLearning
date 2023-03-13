/* File Name Hash.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-10-08 11:30
 * Last Modified 2022-10-08 11:47
 */
#include "linuxHeader.h"
#include "Hash.h"
#include <openssl/sha.h>
Hash::Hash(std::string filename)
    :_filename(filename) {}
std::string Hash::sha1() {
    int fd = open(_filename.c_str(),O_RDONLY);
    char buf[4096];
    SHA_CTX ctx;
    SHA1_Init(&ctx);

    while(true) {
        bzero(buf,sizeof(buf));
        int ret = read(fd,buf,sizeof(buf));
        if(ret == 0) {
            break;
        }
        SHA1_Update(&ctx,buf,ret);
    }
    unsigned char md[20];
    SHA1_Final(md,&ctx);
    char frag[3];
    std::string shalRes;
    for(int i = 0; i < 20; ++i) {
        sprintf(frag,"%02x",md[i]);
        shalRes = shalRes + frag;
    }
    return shalRes;
}

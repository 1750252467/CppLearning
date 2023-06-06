#include "Hash.h"
#include "Crypt.h"
#include "Token.h"
int main(){
    //Hash hash("./tmp/test.pdf");
    //fprintf(stderr,"hash = %s\n", hash.sha1().c_str());
    //Crypt crypt("123","12345678");
    //fprintf(stderr,"crypt = %s\n", crypt.encoded().c_str());
    Token token("admin","12345678");
    fprintf(stderr,"token = %s\n", token.getToken().c_str());
}
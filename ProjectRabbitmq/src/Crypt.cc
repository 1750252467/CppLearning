#include "Crypt.h"
#include "unixHeader.h"
Crypt::Crypt(std::string key, std::string salt)
    :_key(key),_salt(salt){

    }

std::string Crypt::encoded(){
    std::string res = crypt(_key.c_str(),_salt.c_str());
    return res;
}
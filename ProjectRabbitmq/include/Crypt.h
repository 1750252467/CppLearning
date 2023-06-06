#include <string>
#ifndef __CRYPT_H__
#define __CRYPT_H__
class Crypt{
public:
    Crypt(std::string key, std::string salt);
    std::string encoded();
private:
    std::string _key;
    std::string _salt;
};

#endif
#include <string>
#ifndef __HASH_H__
#define __HASH_H__
class Hash{
public:
    Hash(std::string filename);
    std::string sha1();
private:
    std::string _filename;
};
#endif

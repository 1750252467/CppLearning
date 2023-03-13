/* File Name Hash.h
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-10-08 11:27
 * Last Modified 2022-10-08 11:30
 */
#ifndef __HASH_H__
#define __HASH_H__
#include <string>

class Hash{
public:
    Hash(std::string filename);
    std::string sha1();

private:
    std::string _filename;
};


#endif // __HASH_H__

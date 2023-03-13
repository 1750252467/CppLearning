/* File Name test.cc
 * Author 泷fengyoukai
 * Github https://github.com/1750252467
 * Created Time 2022-10-08 15:36
 * Last Modified 2022-10-08 15:44
 */
#include "Hash.h"


int main() {

    Hash hash("./tmp/1.txt");
    fprintf(stderr,"hash = %s\n",hash.sha1().c_str());
    return 0;
}

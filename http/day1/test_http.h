/* File Name           test_http.h
 * Author              泷
 * Github               https://github.com/1750252467
 * Created Time        2022-09-21 15:34
 * Last Modified 2022-09-21 16:43
 */

#ifndef __TEST_HTTP_H__
#define __TEST_HTTP_H__
#include <sys/types.h>       
#include <sys/stat.h>        
#include <fcntl.h>           
#include <unistd.h>          
#include <sys/socket.h>      
#include <netinet/in.h>      
#include <arpa/inet.h>       
#include <string>          
#include <strings.h>
#include <stdlib.h>          
#include <iostream>          
#include <memory>            

namespace search_engine{                
                                        
class TestHttp{                        
public:                                 
    TestHttp(const char *ip, const char* port);                          

    int start();

    int recvAndShow();
private:                                
    const char* _ip;
    const char* _port;
    int _sockfd;
};                                      
                                        
} // namespace search_engine            
                                        
#endif // __TEST_HTTP_H__               

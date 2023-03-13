/* File Name           test_http.cc
 * Author              泷
 * Github               https://github.com/1750252467
 * Created Time        2022-09-21 15:39
 * Last Modified 2022-09-21 17:24
 */
#include "test_http.h"

using std::string;
namespace search_engine{

TestHttp::TestHttp(const char *ip, const char* port)
:_ip(ip)
,_port(port)
{

}

int TestHttp::start() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(_ip);
    addr.sin_port = htons(atoi(_port));
    int reuse = 1;
    setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
     bind(_sockfd, (struct sockaddr* )&addr, sizeof(addr));
    listen(_sockfd, 10);
    return 0;
}

int TestHttp::recvAndShow() {
    int netfd = accept(_sockfd, NULL, NULL);

    std::unique_ptr<char []> buf(new char[4096]);
    bzero(buf.get(),4096);
    recv(netfd,buf.get(),4096,0);
    fprintf(stderr,"%s\n",buf.get());
    string firstLine = "HTTP/1.1 200 OK\r\n";
    send(netfd,firstLine.c_str(),firstLine.size(),0);
    string type = "Content-Type:text/plain\r\n"
        "Content-Length:5\r\n";
    send(netfd,type.c_str(),type.size(),0);
    string emptyline = "\r\n";
    send(netfd,emptyline.c_str(),emptyline.size(),0);
    string connect = "hello";
    send(netfd,connect.c_str(),connect.size(),0);

    close(netfd);
    fprintf(stderr,"closed\n");
    return 0;

}
};
int main(void) {
    search_engine::TestHttp test("0.0.0.0", "8888");
    test.start();

    while(1) {
        test.recvAndShow();
    }
    return 0;
}


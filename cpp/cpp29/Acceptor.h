#ifndef __Acceptor_H__
#define __Acceptor_H__


#include "Socket.h"
#include "InetAddress.h"
#include <string>

using std::string;

class Acceptor
{
public:
    Acceptor(const string &ip,unsigned short port);
    ~Acceptor();
    void ready();
    void setReuseAddr();//地址重用
    void setReusePort();//端口重用 
    void bind();
    void listen();
    int accept();
    int fd() const;
private:
    Socket _listenSock;
    InetAddress _servAddr;
};




#endif

#include "TcpConnection.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd)
:_sock(fd)
,_sockIO(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection(){}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(),msg.size());
}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readline(buff,sizeof(buff));

    return string(buff);
}
string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();
    return oss.str();
}

bool TcpConnection::isClosed()
{
    char buf[10] = {0};
    int ret = ::recv(_sock.fd(),buf,sizeof(buf),MSG_PEEK);

    return 0 == ret;
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb)
{
    _onConnection = cb;

}


void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onConnection = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onClose = cb;
}

void TcpConnection::handleConnectionCallback()
{
    if(_onConnection)
    {
        _onConnection(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        _onMessage(shared_from_this());

    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose(shared_from_this());
    }
}
//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //库里有getsockname
    int ret  = getsockname(_sock.fd(),(struct sockaddr *)&addr,&len);
    if(-1 == ret)
    {
        perror("getsockname");
    }
    return InetAddress(addr);

}
//获取对端的网络地址信息

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = getpeername(_sock.fd(),(struct sockaddr *)&addr,&len);
    if(-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}




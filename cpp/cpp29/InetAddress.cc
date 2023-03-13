#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress(const string &ip, unsigned short port)
{
    ::bzero(&_addr,sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;//ipv4
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

//直接传入整个结构体
InetAddress::InetAddress(const struct sockaddr_in &addr)
:_addr(addr)
{

}

InetAddress::~InetAddress()
{

}

string InetAddress::ip() const
{//将网络字节序ip地址转为点分十进制IP地址
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const
{
    //将网络字节序转换为主机字节序
    return ntohs(_addr.sin_port);

}

const struct sockaddr_in *InetAddress::getInetAddrPtr() const
{
    return &_addr;
}

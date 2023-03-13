#ifndef __InetAddress_H__
#define __InetAddress_H__

#include <arpa/inet.h>
#include <string>

using std::string;

class InetAddress
{
private:
    struct sockaddr_in _addr;
public:
    InetAddress(const string &ip,unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();
    string ip() const;
    unsigned short port() const;
    const struct sockaddr_in *getInetAddrPtr() const;

};





#endif

#ifndef __SocketIO_H__
#define __SocketIO_H__

class SocketIO
{
public:
    explicit SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf,int len);
    int readline(char *buf,int len);
    int writen(const char *buf,int len);
private:
    int _fd;
};





#endif

 ///
 /// @file    readv.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 10:15:45
 ///
 
#include <head.h>
 
int main(int argc, char *argv[])
{
	char buff1[11] = {0};
	char buff2[20] = {0};

	struct iovec ios[2];
	ios[0].iov_base = buff1;
	ios[0].iov_len = 10;//先填满第一个缓冲区，再填第二个
	ios[1].iov_base = buff2;
	ios[1].iov_len = 20;

	int fd = open("file", O_RDWR);
	readv(fd, ios, 2);//分散读

	printf("buff1:%s", buff1);
	printf("buff2:%s\n", buff2);
 
	return 0;
}

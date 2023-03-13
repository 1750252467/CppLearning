 ///
 /// @file    writev.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 10:11:46
 ///
 
#include <head.h>
 
int main(int argc, char *argv[])
{
	char buff1[] = "hi,";
	char buff2[] = "wuhan";

	struct iovec ios[2];
	ios[0].iov_base = buff1;
	ios[0].iov_len = strlen(buff1);
	ios[1].iov_base = buff2;
	ios[1].iov_len = strlen(buff2);

	int fd = open("file", O_RDWR);
	writev(fd, ios, 2);//聚集写
	close(fd);
	return 0;
}

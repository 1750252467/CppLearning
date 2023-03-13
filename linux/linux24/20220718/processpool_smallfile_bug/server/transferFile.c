 ///
 /// @file    transferFile.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 16:26:15
 ///
 
#include "process_pool.h"

#define FILENAME "file"
#define BUFFSIZE 1000

//TCP是一个字节流协议，消息没有边界

int transferfile(int peerfd)
{
	//1. 读取本地文件
	int fd = open(FILENAME, O_RDWR);
	ERROR_CHECK(fd, -1, "open");

	//2. 先发文件名
	send(peerfd, FILENAME, strlen(FILENAME), 0);

	//3. 再发文件内容
	char buff[BUFFSIZE] = {0};
	read(fd, buff, sizeof(buff));
	send(peerfd, buff, strlen(buff), 0);

	close(fd);
}

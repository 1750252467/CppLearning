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
	train_t train;
	memset(&train, 0, sizeof(train));
	train.length = strlen(FILENAME);
	strcpy(train.buff, FILENAME);
	int ret = send(peerfd, &train, 4 + train.length, 0);

	//3. 再发文件内容
	char buff[BUFFSIZE] = {0};
	ret = read(fd, buff, sizeof(buff));
	memset(&train, 0, sizeof(train));
	train.length = ret;
	strncpy(train.buff, buff, ret);
	send(peerfd, &train, 4 + train.length, 0);

	//结论:用TCP发送任何数据，要确保双方都知道
	//消息的边界在哪里,即先发数据的长度，再发数据本身
	//对端在接收时，先接长度，再接数据本身

	close(fd);
}

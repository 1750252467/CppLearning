 ///
 /// @file    transferFile.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 16:26:15
 ///
 
#include "process_pool.h"

#define FILENAME "bigfile.avi"
#define BUFFSIZE 1000

//TCP是一个字节流协议，消息没有边界

int transferfile(int peerfd)
{
	//0. 创建一条管道
	int fds[2];
	pipe(fds);

	//1. 读取本地文件
	int fd = open(FILENAME, O_RDWR);
	ERROR_CHECK(fd, -1, "open");

	//2. 先发文件名
	train_t train;
	memset(&train, 0, sizeof(train));
	train.length = strlen(FILENAME);
	strcpy(train.buff, FILENAME);
	int ret = send(peerfd, &train, 4 + train.length, MSG_WAITALL);

	//3. 再发文件内容
	//3.1 获取文件的长度
	struct stat st;
	fstat(fd, &st);
	printf("file's length: %ld\n", st.st_size);
	//printf("sizeof(st.st_size): %ld\n", sizeof(st.st_size));
	send(peerfd, &st.st_size, 8, MSG_WAITALL);

	//3.2 直接发送(零拷贝技术之三splice)
	size_t sendSize = 0;
	while(sendSize < st.st_size) {
		ret = splice(fd, NULL, fds[1], NULL, 4096, SPLICE_F_MORE);
		ret = splice(fds[0], NULL, peerfd, NULL, ret, SPLICE_F_MORE);
		sendSize += ret;
	}
	printf("splice over\n");
	close(fd);
}

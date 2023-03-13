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
	char buff[BUFFSIZE] = {0};
	struct stat st;
	fstat(fd, &st);
	printf("file's length: %ld\n", st.st_size);
	//printf("sizeof(st.st_size): %ld\n", sizeof(st.st_size));
	send(peerfd, &st.st_size, 8, MSG_WAITALL);

	//3.2 进行映射(零拷贝技术之一)
	char * pbuf = mmap(NULL, st.st_size, 
			PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	//4. 直接发送
	ret = send(peerfd, pbuf, st.st_size, MSG_WAITALL);
	printf(">> send ret: %d\n", ret);

	munmap(pbuf, st.st_size);
	close(fd);
}

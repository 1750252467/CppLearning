#include "process_pool.h"
#include "func.h"
#define FILENAME "bigfile.avi"
#define BUFFSIZE 1000

//TCP是一个字节流协议，消息没有边界

int transferfile(int peerfd)
{
	//1. 读取本地文件
	int fd = open(FILENAME, O_RDWR);//在宏定义里，要传的文件名
	ERROR_CHECK(fd, -1, "open");

	//2. 先发文件名
	train_t train;
	memset(&train, 0, sizeof(train));
	train.length = strlen(FILENAME);
	strcpy(train.buff, FILENAME);
    //MSG_WAITALL 等待信息完整发过去
	int ret = send(peerfd, &train, 4 + train.length, MSG_WAITALL);

	//3. 再发文件内容
	//3.1 获取文件的长度
	char buff[BUFFSIZE] = {0};
	struct stat st;
	fstat(fd, &st);
	printf("file's length: %ld\n", st.st_size);
	//printf("sizeof(st.st_size): %ld\n", sizeof(st.st_size));
	send(peerfd, &st.st_size, 8, MSG_WAITALL);
	size_t sendSize = 0;
	while(sendSize < st.st_size) {
		memset(&train, 0, sizeof(train));
		//从本地文件中读取,将其放入train
		ret = read(fd, train.buff, sizeof(train.buff)); 
		train.length = ret;
		//发送数据给到对端
		ret = send(peerfd, &train, 4 + train.length, MSG_WAITALL);
		if(ret > 0) {
			sendSize += (ret - 4);
		}else {
			perror("send");
			break;
		}
	}

	//结论:用TCP发送任何数据，要确保双方都知道
	//消息的边界在哪里,即先发数据的长度，再发数据本身
	//对端在接收时，先接长度，再接数据本身

	close(fd);
}

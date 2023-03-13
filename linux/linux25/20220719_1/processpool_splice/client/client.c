 ///
 /// @file    client.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-12 16:08:45
 ///
 
#include <head.h>


int recvCircle(int fd, char * buff, int length)
{
	char * pbuf = buff;
	int left = length;
	int ret = 0;
	while(left > 0) {
		ret = recv(fd, pbuf, left, 0);
		if(0 == ret) {
			close(fd);
			break;
		} else if(ret == -1 && errno == EINTR) {
			continue;
		} else if(ret == -1) {
			perror("recv");
			break;
		} else {// > 0
			pbuf += ret;
			left -= ret;
		}
	}
	return length - left;
}
 
int main(int argc, char *argv[])
{
	//0. 创建套接字
	int clientfd = socket(AF_INET, SOCK_STREAM, 0);
	ERROR_CHECK(clientfd, -1, "socket");

	printf("sizeof(struct sockaddr):%ld\n", sizeof(struct sockaddr));
	printf("sizeof(struct sockaddr_in):%ld\n", sizeof(struct sockaddr_in));

	//1. 设置服务器的网络地址
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int ret = connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	ERROR_CHECK(ret, -1, "connect");
	printf("conn has connected\n");

	//1. 先接文件名
	char filename[100] = {0};
	
	//recv第三个参数最多能接1000个字节数据
	int length = 0;
	//recv(clientfd, &length, 4, MSG_WAITALL);
	recvCircle(clientfd, (char*)&length, 4);
	printf("file length: %d\n", length);
	//recv(clientfd, filename, length, MSG_WAITALL);
	recvCircle(clientfd, filename, length);
	printf(">> filename:%s\n", filename);

	int fd = open(filename, O_RDWR|O_CREAT, 0644); 
	//2. 再接收文件内容
	//2.1 先接文件长度
	size_t filelength = 0;
	//recv(clientfd, &filelength, 8, MSG_WAITALL);
	recvCircle(clientfd, (char*)&filelength, 8);
	printf("filecontent length: %ld\n", filelength);

	//2.2 再接文件内容
	size_t recvSize = 0;
	while(recvSize < filelength) {
		char buff[1000] = {0};
		//recv(clientfd, &length, 4, MSG_WAITALL);
		recvCircle(clientfd, (char*)&length, 4);
		//recv(clientfd, buff, length, MSG_WAITALL);
		recvCircle(clientfd, buff, length);
		//3. 写入本地
		write(fd, buff, length);
		recvSize += length;
	}
	close(fd);
	close(clientfd);
}

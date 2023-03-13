 ///
 /// @file    client.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-12 16:08:45
 ///
 
#include <head.h>
 
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
	char filename[1000] = {0};
	
	//recv第三个参数最多能接1000个字节数据
	recv(clientfd, filename, sizeof(filename), 0);
	printf(">> filename:%s\n", filename);

	int fd = open(filename, O_RDWR|O_CREAT); 
	//2. 再接收文件内容
	char buff[1000] = {0};
	recv(clientfd, buff, sizeof(buff), 0);
	printf("buff: %s\n", buff);
	
	//3. 写入本地
	write(fd, buff, strlen(buff));

	close(fd);
	close(clientfd);
}

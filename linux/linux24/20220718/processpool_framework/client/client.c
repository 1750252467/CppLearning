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

	fd_set rdset;

	while(1) {
		FD_ZERO(&rdset);
		FD_SET(clientfd, &rdset);
		FD_SET(STDIN_FILENO, &rdset);

		select(clientfd + 1, &rdset, NULL, NULL, NULL);

		if(FD_ISSET(STDIN_FILENO, &rdset)) {
			char recvbuff[100] = {0};
			read(STDIN_FILENO, recvbuff, sizeof(recvbuff));
			write(clientfd, recvbuff, strlen(recvbuff));
		}

		if(FD_ISSET(clientfd, &rdset)) {
			char recvbuff[100] = {0};
			int ret = read(clientfd, recvbuff, sizeof(recvbuff));
			if(ret == 0) {
				break;
			}
			printf("recv from server: %s\n", recvbuff);
		}
	}

	close(clientfd);
}

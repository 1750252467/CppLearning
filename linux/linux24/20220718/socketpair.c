 ///
 /// @file    pipe.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 09:46:21
 ///
 
#include <head.h>

int sendFd(int pipefd, int fd);
int recvFd(int pipefd, int * childfd);
 
int main(int argc, char *argv[])
{
	int fds[2];
	//pipe(fds);
	//socketpair只能用于父子进程之间, 全双工的
	socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
	printf("fds[0]: %d, fds[1]: %d\n", fds[0], fds[1]);

	pid_t pid = fork();
	if(pid > 0) {
		//父进程写
		close(fds[0]);
		int fd = open("file", O_RDWR);//模拟远程客户端client
		printf("parent fd: %d\n", fd);
		//write(fds[1], &fd, sizeof(fd));
		sendFd(fds[1], fd);
		wait(NULL);
	} else {
		//子进程读
		close(fds[1]);
		int childfd;
		//read(fds[0], &childfd, sizeof(childfd));
		recvFd(fds[0], &childfd);
		printf("childfd: %d\n", childfd);

		char buff[20] = {0};
		read(childfd, buff, 20);//子进程中的childfd与父进程中的fd指向的是内核中同一个文件对象
		printf("buff:%s\n", buff);
	}
	return 0;
}

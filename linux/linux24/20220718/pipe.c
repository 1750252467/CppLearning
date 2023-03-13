 ///
 /// @file    pipe.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 09:46:21
 ///
 
#include <head.h>
 
int main(int argc, char *argv[])
{
	int fds[2];
	pipe(fds);
	printf("fds[0]: %d, fds[1]: %d\n", fds[0], fds[1]);

	pid_t pid = fork();
	if(pid > 0) {
		//父进程写
		close(fds[0]);
		int fd = open("file", O_RDWR);
		printf("parent fd: %d\n", fd);
		write(fds[1], &fd, sizeof(fd));
		wait(NULL);
	} else {
		//子进程读
		close(fds[1]);
		int childfd;
		read(fds[0], &childfd, sizeof(childfd));
		printf("childfd: %d\n", childfd);

		char buff[20] = {0};
		read(childfd, buff, 20);
		printf("buff:%s\n", buff);
	}
	return 0;
}

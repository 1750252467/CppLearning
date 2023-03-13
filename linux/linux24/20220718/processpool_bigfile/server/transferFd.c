 ///
 /// @file    transferFd.c
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2022-07-18 11:00:00
 ///
 
#include <func.h>
 
int sendFd(int pipefd, int fd)
{
	//1. 构造struct iovec数组
	char buff[10] = "a";
	struct iovec iov;
	iov.iov_base = buff;
	iov.iov_len = strlen(buff);

	//2. 构造struct cmsghdr
	size_t len = CMSG_LEN(sizeof(fd));
	//printf(">> cmsghdr's len: %ld\n", len);
	struct cmsghdr * pcmsghdr = (struct cmsghdr*)calloc(len, 1);
	pcmsghdr->cmsg_len = len;
	pcmsghdr->cmsg_level = SOL_SOCKET;
	pcmsghdr->cmsg_type = SCM_RIGHTS;
	int * p = (int*)CMSG_DATA(pcmsghdr);//拿到存储数据的首地址
	*p = fd;//赋值

	//3. 构造struct msghdr
	struct msghdr mhdr;
	memset(&mhdr, 0, sizeof(mhdr));
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;
	mhdr.msg_control = pcmsghdr;
	mhdr.msg_controllen = len;

	//4. 发送消息
	int ret = sendmsg(pipefd, &mhdr, 0);
	ERROR_CHECK(ret, -1, "sendmsg");
	return ret;
}

int recvFd(int pipefd, int * childfd)
{
	//1. 构造struct iovec数组
	char buff[10] = {0};
	struct iovec iov;
	iov.iov_base = buff;//接收消息时，准备好空间即可
	iov.iov_len = sizeof(buff);

	//2. 构造struct cmsghdr
	size_t len = CMSG_LEN(sizeof(int));
	//printf(">> cmsghdr's len: %ld\n", len);
	struct cmsghdr * pcmsghdr = (struct cmsghdr*)calloc(len, 1);
	pcmsghdr->cmsg_len = len;
	pcmsghdr->cmsg_level = SOL_SOCKET;
	pcmsghdr->cmsg_type = SCM_RIGHTS;

	//3. 构造struct msghdr
	struct msghdr mhdr;
	memset(&mhdr, 0, sizeof(mhdr));
	mhdr.msg_iov = &iov;
	mhdr.msg_iovlen = 1;
	mhdr.msg_control = pcmsghdr;
	mhdr.msg_controllen = len;

	//4. 接收消息
	int ret = recvmsg(pipefd, &mhdr, 0);
	ERROR_CHECK(ret, -1, "recvmsg");
	int * p = (int*)CMSG_DATA(pcmsghdr);//拿到存储数据的首地址
	*childfd = *p;//*p读取fd, 再传递出去, 进行赋值即可
	//printf(">> recvFd buff:%s\n", buff);
	return ret;
}

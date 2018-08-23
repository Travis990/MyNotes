#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
	// 创建套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
	{
		perror("socket");
	}

	// 连接
	struct sockaddr_in myaddr;
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8080); // 将2个字节端口转大端,服务器的端口
	// IP地址点转十进制
	inet_pton(AF_INET, "192.168.11.44", &myaddr.sin_addr.s_addr);//ip是服务器的ip

	connect(fd, (struct sockaddr*)&myaddr, sizeof(myaddr));

	// 读写
	char buf[1024] = "";
	while(1)
	{
		write(fd, "hello", strlen("hello"));
		read(fd, buf, sizeof(buf));

		printf("buf = %s\n", buf);
	}
	
	// 关闭
	close(fd);

	return 0;
}

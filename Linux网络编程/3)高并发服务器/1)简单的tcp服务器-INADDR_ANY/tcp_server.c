#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	// 创建套接字
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	// 绑定
	struct sockaddr_in myaddr;
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(9000);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	int ret1 = 0;
	// inet_pton(AF_INET,"192.168.11.251",&myaddr.sin_addr.s_addr);
	ret1 = bind(sock_fd, (struct sockaddr*)&myaddr, sizeof(myaddr)); // 绑定
	if(ret1 < 0)
	{
		perror("bind");
	}
	// 监听
	listen(sock_fd, 128);
	// 提取
	struct sockaddr_in cliaddr;
	socklen_t len;
	printf("call accept\n");
	// 提取链接,将提取到的连接的信息存放在结构体cliaddr中
	int cfd = accept(sock_fd, (struct sockaddr*)&cliaddr, &len);
	printf("call accept ok\n");
	char ip[16] = "";
	// 打印提取的信息 ip  port
	printf("ip=%s port=%d\n", 
			inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr,ip,16),
			ntohs(cliaddr.sin_port)
			);
	// 读写
	char buf[1500] = "";
	int ret = 0;
	// 回射服务器  收到什么 给对方回什么
	while(1)
	{
		ret = read(cfd, buf, sizeof(buf));
		if(ret < 0)
		{
			perror("read");
			break;
		}
		else if(0 == ret) // 读到0长度的数据包,代表对方关闭
		{
			printf("client close\n");
			break;
		}
		else
		{
			printf("%s\n", buf);
			write(cfd, buf, ret);
		}
	}

	// 关闭
	close(cfd);
	close(sock_fd);

	return 0;
}

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "wrap.h"

int main(int argc, char** argv)
{
	// 创建套接字
	// 绑定
	int l_fd = tcp4bind(9000,NULL);
	// 监听
	listen(l_fd, 128);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	char ip[INET_ADDRSTRLEN] = {0};
	pid_t pid;
	while(1)
	{
		// 提取
		int c_fd = accept(l_fd, (struct sockaddr*)&cliaddr, &len);
		printf("new client ip:%s port:%d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, INET_ADDRSTRLEN),
				ntohs(cliaddr.sin_port)
		);
		// 创建子进程
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
		}
		else if(0 == pid) // 子进程
		{
			close(l_fd); // 关闭监听套接字
			int ret = 0;
			char recv_buf[1024] = "";
			while(1)
			{
				ret = Read(c_fd, recv_buf, sizeof(recv_buf));
				if(ret < 0)
				{
					perror("Read");
					break;
				}
				else if(0 == ret)
				{
					printf("client close\n");
					break;
				}
				else
				{
					printf("%s\n", recv_buf);
					Write(c_fd, recv_buf, ret);
				}
			}
			close(c_fd); // 关闭已连接套接字
		}
		else // 父进程
		{
			close(c_fd);

			// 回收资源
		}
	}

	return 0;	
}

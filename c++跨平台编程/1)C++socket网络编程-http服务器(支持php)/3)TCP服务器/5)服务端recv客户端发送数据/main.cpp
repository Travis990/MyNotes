// Windows编译步骤:
// 项目属性>>链接器>>输入>>附加依赖项>> "ws2_32.lib;..."
// C/C++>>预处理器>>预处理器定义>> "WIN32;..."

// Linux编译步骤:
// make main

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define closesocket close
#endif // Windows

#include <stdio.h>

int main(int argc, char** argv)
{
#ifdef WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
#endif // Windows

	// Linux 下sock文件描述符最大个数是 1024 , 查看文件描述符最大数: ulimit -n , 修改文件描述符最大个数限制: ulimit -n 3000
	int sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
	if (-1 == sock)
	{
		printf("create socket failed!\n");   // 在windows当中几乎很难失败, 除非系统资源占用过大耗尽了才会
		return -1;                           // 在Linux下 因为系统规定的进程句柄数量有限的(描述符最大值1024), 如超出了1024就好失败
	}
	
	unsigned short port = 8080;
	if (argc > 1) port = atoi(argv[1]);

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port); // 主机字节序 转 网络字节序 (大端)
	saddr.sin_addr.s_addr = htonl(0);
	
	if (0 != bind(sock, (sockaddr*)&saddr, sizeof(saddr)))
	{
		printf("bind port %d failed!\n", port);
		return -2;
	}
	printf("bind port %d success!\n", port);
	listen(sock, 10);

	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len); // 提取客户端socket, 独立的
	printf("accept client %d \n", client);
	const char* ip = inet_ntoa(caddr.sin_addr);
	unsigned short cport = ntohs(caddr.sin_port);
	printf("client ip is %s, port is %d\n", ip, cport);

	char buf[1024] = {0};
	int recvlen = recv(client, buf, sizeof(buf) - 1, 0);
	printf("recv %s \n", buf);
	closesocket(client);

	// 客户端测试: telnet 192.168.163.131 8080
	
	//closesocket(sock);
	getchar();
	return 0;
}
#include "XUdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#define closesocket close
#endif // Windows

XUdp::XUdp()
{
#ifdef WIN32
	static bool first = true;
	if (first)
	{
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif // Windows
	memset(ip, 0, sizeof(ip));
}

int XUdp::CreateSocket()
{
	// Linux 下sock文件描述符最大个数是 1024 , 查看文件描述符最大数: ulimit -n , 修改文件描述符最大个数限制: ulimit -n 3000
	sock = socket(AF_INET, SOCK_DGRAM, 0); // UDP
	if (-1 == sock)
	{
		printf("create socket failed!\n");   // 在windows当中几乎很难失败, 除非系统资源占用过大耗尽了才会
											 // 在Linux下 因为系统规定的进程句柄数量有限的(描述符最大值1024), 如超出了1024就好失败
	}
	return sock;
}

bool XUdp::Bind(unsigned short port)
{
	if (sock <= 0) CreateSocket();

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port); // 主机字节序 转 网络字节序 (大端)
	saddr.sin_addr.s_addr = htonl(0);

	if (0 != ::bind(sock, (sockaddr*)&saddr, sizeof(saddr)))
	{
		printf("bind port %d failed!\n", port);
		return false;
	}
	printf("bind port %d success!\n", port);
	listen(sock, 10);
	return true;
}

int XUdp::Recv(char* buf, int bufsize)
{
	if (sock <= 0) return 0;
	if (addr == 0)
	{
		addr = new sockaddr_in();
	}
	socklen_t len = sizeof(sockaddr_in);
	int re = recvfrom(sock, buf, bufsize, 0, (sockaddr*)addr, &len);
	return re;
}

void XUdp::Close()
{
	if (sock <= 0) return;
	closesocket(sock);
	if (addr)
	{
		delete addr;
	}
	addr = 0;
	sock = 0;
}

XUdp::~XUdp()
{
}

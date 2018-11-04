// 要记住一点: 头文件的引用要尽量放在.cpp当中!
// 为什么要放在.cpp当中而不放在.h当中呢? 
// .h文件如果是被第三方引用,那就涉及到了什么?
// 对于调用者来说,他只要知道.h就行了.需不需要知道.cpp?不需要!
// 甚至.cpp我们可以把它变成动态链接库,但.h文件还是需要给他的
// 如果你.h中有比如windows.h,那就有可能给调用者造成冲突影响!
// 为什么给调用者造成冲突影响呢?
// 答: 比如std::bind()命名空间函数与windows.h中的::bind()函数调用冲突


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>
#include "XTcp.h"

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

//#include <thread>
//using namespace std;


XTcp::XTcp()
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
}

int XTcp::CreateSocket()
{
	// Linux 下sock文件描述符最大个数是 1024 , 查看文件描述符最大数: ulimit -n , 修改文件描述符最大个数限制: ulimit -n 3000
	sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
	if (-1 == sock)
	{
		printf("create socket failed!\n");   // 在windows当中几乎很难失败, 除非系统资源占用过大耗尽了才会
		                                     // 在Linux下 因为系统规定的进程句柄数量有限的(描述符最大值1024), 如超出了1024就好失败
	}
	return sock;
}

bool XTcp::Bind(unsigned short port)
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

XTcp XTcp::Accept()
{
	XTcp tcp;
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len); // 提取客户端socket, 独立的
	if (client <= 0) return tcp;
	printf("accept client %d \n", client);
	char* ip = inet_ntoa(caddr.sin_addr);
	strcpy(tcp.ip, ip);
	tcp.port = ntohs(caddr.sin_port);
	tcp.sock = client;
	printf("client ip is %s, port is %d\n", tcp.ip, tcp.port);
	return tcp;
}

void XTcp::Close()
{
	if (sock <= 0) return;
	closesocket(sock);
}

int XTcp::Recv(char* buf, int bufsize)
{
	return recv(sock, buf, bufsize, 0);
}

int XTcp::Send(const char* buf, int bufsize)
{
	int sendedSize = 0;
	while (sendedSize != bufsize)
	{
		int len = send(sock, buf + sendedSize, bufsize - sendedSize, 0);
		if (len <= 0) break;
		sendedSize += len;
	}
	return sendedSize;
}

bool XTcp::Connect(const char* ip, unsigned short port)
{
	if (sock <= 0) CreateSocket();

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ip);
	if (connect(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		printf("connect %s:%d failed!:%s\n", ip, port, strerror(errno));
		return false;
	}
	printf("connect %s:%d success!\n", ip, port);
	return true;
}

bool XTcp::SetBlock(bool isblock)
{
	if (sock <= 0) return false;
#ifdef WIN32
	unsigned long ul = 0;
	if (!isblock) ul = 1;
	ioctlsocket(sock, FIONBIO, &ul);
#else
	int flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0) return false;
	if (isblock)
	{
		flags = flags&~O_NONBLOCK;
	}
	else
	{
		flags = flags|O_NONBLOCK;
	}
	if (fcntl(sock, F_SETFL, flags) != 0) return false;
#endif
	return true;
}

XTcp::~XTcp()
{
}

#include <iostream>
#include <stdexcept>

#ifdef _MBCS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN  // 解决#include <WinSock2.h> 里面有重定义的问题
#define _WINSOCK_DEPRECATED_NO_WARNINGS // inet_ntoa()过时问题

#include <Windows.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
#endif

using namespace std;

int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	try {
		//--------------
		//-- 用Socket API建立简易TCP服务器
		// 1 建立一个socket 套接字
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		// 2 bind 绑定用于接受客户端连接的网络端口
		sockaddr_in _sin;
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(9000); // host to net unsigned short
		_sin.sin_addr.s_addr = INADDR_ANY;// inet_addr("0.0.0.0");
		if (SOCKET_ERROR == bind(sock, (sockaddr*)&_sin, sizeof(_sin)))
		{
			throw runtime_error("ERROR:bind(),绑定端口失败!!\n");
		}
		
		// 3 listen 监听网络端口
		if (SOCKET_ERROR == listen(sock, 5))
		{
			throw runtime_error("ERROR:listen(),监听网络端口失败!!\n");
		}

		// 4 accept 等待接受客户端连接
		sockaddr_in clienAddr;
		int addrlen = sizeof(clienAddr);
		SOCKET _cSock = INVALID_SOCKET;

		_cSock = accept(sock, (sockaddr*)&clienAddr, &addrlen);
		if (INVALID_SOCKET == _cSock)
		{
			throw runtime_error("ERROR:accept(),接收到无效的客户端SOCKET!!\n");
		}
		cout << "新连接客户端IP:" << inet_ntoa(clienAddr.sin_addr)
			 << " 端口:" << clienAddr.sin_port << endl;
		char recvBuf[128] = {0};
		while(true)
		{ 
			// 5 接收服务器端数据
			int recvlen = recv(_cSock, recvBuf, 128, 0);
			if (recvlen <= 0)
			{
				cout << "客户端已退出, 任务结束!" << endl;
				break;
			}
			// 6 处理请求
			if ( 0 == strcmp(recvBuf, "getName") )
			{
				// 7 send 向客户端发送一条数据
				char msgBuf[] = "Dejan";
				send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
			}
			else if ( 0 == strcmp(recvBuf, "getAge") )
			{
				// 7 send 向客户端发送一条数据
				char msgBuf[] = "22";
				send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
			}
			else 
			{
				// 7 send 向客户端发送一条数据
				char msgBuf[] = "???";
				send(_cSock, msgBuf, strlen(msgBuf) + 1, 0); // +1 是 加字符\0
			}
		}

		// 8 关闭套接字closesocket
		closesocket(sock);

		//--------------
	}
	catch (const exception &e)
	{
		cerr << "Get exception : " << e.what() << endl;
	}
	
	WSACleanup();
	system("pause");
	return 0;
}
#include <iostream>
#include <stdexcept>

#ifdef _MBCS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN  // 解决#include <WinSock2.h> 里面有重定义的问题
#define _WINSOCK_DEPRECATED_NO_WARNINGS // inet_ntoa()、inet_addr()过时问题

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
		//-- 用Socket API创建简易的TCP客户端
		// 1 建立一个socket
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == sock)
		{
			throw runtime_error("ERROR:socket(),创建SOCKET失败!!\n");
		}

		// 2 连接服务器 connect
		sockaddr_in _sin;
		_sin.sin_family = AF_INET;
		_sin.sin_port = htons(9000);
		_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
		if (SOCKET_ERROR == connect(sock, (sockaddr*)&_sin, sizeof(_sin)))
		{
			throw runtime_error("ERROR:connect(),连接服务器失败!!\n");
		}

		while (true)
		{
			// 3 输入请求命令
			char cmdBuf[128] = { 0 };
			cin >> cmdBuf;
			// 4 处理请求命令
			if (0 == strcmp(cmdBuf, "exit"))
			{
				break;
			}
			else 
			{
				// 5 向服务器发送请求指令
				send(sock, cmdBuf, strlen(cmdBuf)+1, 0);
			}

			// 6 接收服务器信息 recv
			char recvBuf[128] = { 0 };
			int recvlen = recv(sock, recvBuf, 128, 0);
			if (recvlen > 0)
			{
				cout << recvBuf << endl;
			}
		}

		// 7 关闭套接字 closesocket
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
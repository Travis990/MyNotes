#include <iostream>

#ifdef _MBCS
	#define _CRT_SECURE_NO_WARNINGS
	#define WIN32_LEAN_AND_MEAN  // 解决#include <WinSock2.h> 里面有重定义的问题
	
	#include <Windows.h>
	#include <WinSock2.h>
	
	#pragma comment(lib, "ws2_32.lib")
#endif

using namespace std;

int main()
{
	WORD ver = MAKEWORD(2,2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//--------------
	//-- 用Socket API创建简易的TCP客户端
	// 1 建立一个socket
	// 2 链接服务器 connect
	// 3 接收服务器信息 recv
	// 4 关闭套接字 closesocket
	//-- 用Socket API建立简易TCP服务器
	// 1 建立一个socket
	// 2 bind 绑定用于接受客户端连接的网络端口
	// 3 listen 监听网络端口
	// 4 accept 等待接受客户端连接
	// 5 send 向客户端发送一条数据
	// 6 关闭套接字closesocket
	//--------------
	WSACleanup();

	system("pause");
	return 0;
}
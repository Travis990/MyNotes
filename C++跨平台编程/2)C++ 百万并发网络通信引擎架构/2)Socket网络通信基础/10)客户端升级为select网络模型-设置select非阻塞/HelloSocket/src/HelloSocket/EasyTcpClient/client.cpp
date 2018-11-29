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

enum CMD
{
	CMD_LOGIN,
	CMD_LOGIN_RESULT,
	CMD_LOGOUT,
	CMD_LOGOUT_RESULT,
	CMD_NEW_USER_JOIN,
	CMD_ERROR
};
struct DataHeader
{
	short dataLength;  // 数据长度
	short cmd;
};
struct Login :public DataHeader
{
	Login()
	{
		dataLength = sizeof(Login);
		cmd = CMD_LOGIN;
	}
	char username[32] = { 0 };
	char password[32] = { 0 };
};
struct Logout :public DataHeader
{
	Logout()
	{
		dataLength = sizeof(Logout);
		cmd = CMD_LOGOUT;
	}
	char username[32] = { 0 };
};
struct LoginResult :public DataHeader
{
	LoginResult()
	{
		dataLength = sizeof(LoginResult);
		cmd = CMD_LOGIN_RESULT;
	}
	char result[32] = "登陆成功!";
};
struct LogoutResult :public DataHeader
{
	LogoutResult()
	{
		dataLength = sizeof(LogoutResult);
		cmd = CMD_LOGOUT_RESULT;
	}
	char result[32] = "退出成功!";
};
struct NewUserJoin :public DataHeader
{
	NewUserJoin()
	{
		dataLength = sizeof(NewUserJoin);
		cmd = CMD_NEW_USER_JOIN;
		sock = 0;
	}
	char sock;
};

int processor(SOCKET _cSock)
{
	// 缓冲区
	char szRecv[4096] = { 0 };
	// 5 接收服务器端数据
	int recvlen = recv(_cSock, szRecv, sizeof(DataHeader), 0);
	DataHeader *header = (DataHeader*)szRecv;
	if (recvlen <= 0)
	{
		cout << "与服务器断开连接, 任务结束!" << endl;
		return -1;
	}
	//if (recvlen >= sizeof(DataHeader))

	cout << "收到命令:" << header->cmd << " 数据长度:" << header->dataLength << endl;

	switch (header->cmd)
	{
		case CMD_LOGIN_RESULT: {
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			LoginResult* ret = (LoginResult*)szRecv;
			cout << "收到服务器端返回命令:CMD_LOGIN_RESULT 数据长度:" << ret->dataLength << endl;
			
			break;
		}
		case CMD_LOGOUT_RESULT: {
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			LogoutResult* ret = (LogoutResult*)szRecv;
			cout << "收到服务器端返回命令:CMD_LOGOUT_RESULT 数据长度:" << ret->dataLength << endl;

			break;
		}
		case CMD_NEW_USER_JOIN: {
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			NewUserJoin* userJoin = (NewUserJoin*)szRecv;
			cout << "收到服务器端返回命令:CMD_NEW_USER_JOIN 数据长度:" << userJoin->dataLength << endl;

			break;
		}
	}
}

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
			fd_set fdReads;
			FD_ZERO(&fdReads);
			FD_SET(sock, &fdReads);
			timeval t = {0, 0};
			int ret = select(sock, &fdReads, 0, 0 , &t);
			if (ret < 0)
			{
				cout << "ERROR:select任务结束!" << endl;
				break;
			}
			if (FD_ISSET(sock, &fdReads))
			{
				FD_CLR(sock, &fdReads);

				if (-1 == processor(sock))
				{
					cout << "ERROR:processor(),select任务结束!" << endl;
					break;
				}
			}
			
			cout << "空闲时间处理其他业务.. \n" << endl;
			Login login;
			strcpy(login.username, "Dejan");
			strcpy(login.password, "123456");
			send(sock, (const char*)&login, sizeof(Login), 0);
			Sleep(1000);
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
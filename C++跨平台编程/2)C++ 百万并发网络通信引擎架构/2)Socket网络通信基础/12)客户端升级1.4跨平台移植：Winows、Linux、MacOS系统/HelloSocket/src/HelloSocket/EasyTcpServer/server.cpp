#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define WIN32_LEAN_AND_MEAN  // 解决#include <WinSock2.h> 里面有重定义的问题
	#define _WINSOCK_DEPRECATED_NO_WARNINGS // inet_ntoa()过时问题

	#include <Windows.h>
	#include <WinSock2.h>

	#pragma comment(lib, "ws2_32.lib")

#elif __GNUC__
	#include <sys/types.h>
	#include <sys/socket.h>
	
	#define SOCKET int
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

vector<SOCKET> g_clients;

int processor(SOCKET _cSock)
{
	// 缓冲区
	char szRecv[4096] = { 0 };
	// 5 接收服务器端数据
	int recvlen = recv(_cSock, szRecv, sizeof(DataHeader), 0);
	DataHeader *header = (DataHeader*)szRecv;
	if (recvlen <= 0)
	{
		cout << "客户端<Socket:"<< _cSock <<">已退出, 任务结束!" << endl;
		return -1;
	}
	//if (recvlen >= sizeof(DataHeader))

	cout << "收到命令:" << header->cmd << " 数据长度:" << header->dataLength << endl;

	switch (header->cmd)
	{
		case CMD_LOGIN: {
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			Login* login = (Login*)szRecv;
			cout << "收到命令:" << login->cmd << " 数据长度:" << login->dataLength << " -- ";
			cout << "登陆用户:" << login->username << " 密码:" << login->password << endl;
			// 忽略判断用户密码是否正确的过程
			LoginResult res;
			send(_cSock, (const char*)&res, sizeof(LoginResult), 0);
			break;
		}
		case CMD_LOGOUT: {
			recv(_cSock, szRecv + sizeof(DataHeader), header->dataLength - sizeof(DataHeader), 0);
			Logout* logout = (Logout*)szRecv;
			cout << "收到命令:" << logout->cmd << " 数据长度:" << logout->dataLength << " -- ";
			cout << "退出用户:" << logout->username << endl;
			LogoutResult res;
			send(_cSock, (const char*)&res, sizeof(LogoutResult), 0);
			break;
		}
		default:
		{
			DataHeader header = { 0, CMD_ERROR };
			send(_cSock, (const char*)&header, sizeof(DataHeader), 0);
			break;
		}
	}
}

int main()
{
#ifdef _MSC_VER
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
#endif

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

		
		while(true)
		{ 
			// 伯克利 BSD socket
			fd_set fdRead; // 描述符(socket) 集合
			fd_set fdWrite;
			fd_set fdExp;
			// 清零
			FD_ZERO(&fdRead);
			FD_ZERO(&fdWrite);
			FD_ZERO(&fdExp);
			// 将描述符(socket)加入集合
			FD_SET(sock, &fdRead);
			FD_SET(sock, &fdWrite);
			FD_SET(sock, &fdExp);

			for (int n = g_clients.size()-1; n >= 0; n--)
			{
				FD_SET(g_clients[n], &fdRead);
			}
			// nfds 是一个整数值, 是指fd_set集合中所有描述符(socket)的范围, 而不是数量
			// 既是所有文件描述符最大值+1, 在Windows中这个参数可以写0
			timeval t = {1, 0}; // 设置 select 非阻塞, NULL 是 阻塞的
			int ret = select(sock + 1, &fdRead, &fdWrite, &fdExp, &t);
			if (ret < 0)
			{
				cout << "ERROR:select(),任务结束!\n" << endl;
				break;
			}
			if (FD_ISSET(sock, &fdRead))
			{
				FD_CLR(sock, &fdRead); // 清理
				// 4 accept 等待接受客户端连接
				sockaddr_in clienAddr;
				int addrlen = sizeof(clienAddr);
				SOCKET _cSock = INVALID_SOCKET;

				_cSock = accept(sock, (sockaddr*)&clienAddr, &addrlen);
				if (INVALID_SOCKET == _cSock)
				{
					cout<< "ERROR:accept(),接收到无效的客户端SOCKET!!"<<endl;
				}
				else 
				{
					for (int n = g_clients.size() - 1; n >= 0; n--)
					{
						NewUserJoin userJoin;
						userJoin.sock = _cSock;
						send(g_clients[n], (const char*)&userJoin, sizeof(NewUserJoin), 0);
					}
					g_clients.push_back(_cSock);
					cout << "新连接客户端IP:" << inet_ntoa(clienAddr.sin_addr)
						<< " 端口:" << clienAddr.sin_port << endl;
				}
				
			}
			for (int n = 0; n < fdRead.fd_count; n++)
			{
				if (-1 == processor(fdRead.fd_array[n]))
				{
					auto iter = find(g_clients.begin(), g_clients.end(), fdRead.fd_array[n]);
					if (iter != g_clients.end())
					{
						g_clients.erase(iter);
					}
				}
			}
			cout << "当前在线人数:"<< g_clients.size() << endl;
		}

		for (int n = g_clients.size() - 1; n >= 0; n--)
		{
			closesocket(g_clients[n]);
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
#include <iostream>
#include "TcpServer.h"
#include <cstring>

using namespace std;

int main(void)
{
	int ret = 0;
	
	TcpSocket *pTcpSocket = NULL;
	
	//接收数据相关的参数
	char *recvData = NULL;
	int recvDataLen = 0;
	
	//发送数据
	const char *sendData = "华山论剑";
	
	//1. 构造一个服务端对象
	TcpServer tcpServer;
	
	//2. 设置监听
	//int setListen(unsigned short port);
	ret = tcpServer.setListen(10086);
	if (ret < 0)
	{
		cout << "listen error..." << endl;
	}
	
	//3. 接受客户端连接
	pTcpSocket = tcpServer.acceptConn(10000);
	if (NULL == pTcpSocket)
	{
		cout << "acceptConn failed.. " << endl;
	}
	
	//4. 接收数据
	//int recvMsg(char** recvData, int &recvLen, int timeout = TIMEOUT);
	pTcpSocket->recvMsg(&recvData, recvDataLen, 0);
	
	cout << "RecvData:  " << recvData << endl;
	
	//5. 发送数据
	//int sendMsg(char* sendData, int dataLen, int timeout = TIMEOUT);
	pTcpSocket->sendMsg((char*)sendData, strlen(sendData), 0);
	
	//6. 释放内存
	//void freeMemory(char** buf);
	pTcpSocket->freeMemory(&recvData);
	
	//7. 断开连接
	//void disConnect();
	pTcpSocket->disConnect();
	
	//void closefd();
	tcpServer.closefd();
	
    return 0;
}

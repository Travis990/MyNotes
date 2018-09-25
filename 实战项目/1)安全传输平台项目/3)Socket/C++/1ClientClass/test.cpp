#include <iostream>
#include "TcpSocket.h"
#include <cstring>

using namespace std;

//客户端代码
int main(void)
{
	const char *data = "寻找武当派张三丰";
	

	char *recvData = NULL;
	int recvDataLen = 0;
	


	//1. 构造一个TcpSocket对象
	TcpSocket tcpSocket;
	
	//2. 连接到服务器
	tcpSocket.connectToHost("192.168.11.51", 10086, 1000);
	//cout << "连接服务器ok" << endl;
	
	//3. 发送数据
	//sendMsg(char* sendData, int dataLen, int timeout = TIMEOUT);
	tcpSocket.sendMsg((char *)data, strlen(data), 1000);
	
	//4. 接收数据
	//recvMsg(char** recvData, int &recvLen, int timeout = TIMEOUT);
	tcpSocket.recvMsg(&recvData, recvDataLen, 1000);
	
	cout << "客户端接收到数据: " << recvData << endl;
	
	//5. 释放内存
	//void freeMemory(char** buf);
	tcpSocket.freeMemory(&recvData);
	
	//6. 断开连接
	//void disConnect();
	tcpSocket.disConnect();
	
	
    return 0;
}

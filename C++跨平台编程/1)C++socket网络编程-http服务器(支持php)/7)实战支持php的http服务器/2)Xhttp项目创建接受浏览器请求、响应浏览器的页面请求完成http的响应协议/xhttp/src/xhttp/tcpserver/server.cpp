// Windows编译步骤:
// 项目属性>>链接器>>输入>>附加依赖项>> "ws2_32.lib;..."
// C/C++>>预处理器>>预处理器定义>> "WIN32;..."

// Linux编译步骤:
// make main

#include <iostream>
#include <stdlib.h>
#include <string>
#include <XTcp.h>
#include <thread>
using namespace std;

class XHttpThread
{
public:
	void Main()
	{
		char buf[10000] = {0};
		// 接收http客户端请求
		int recvLen = client.Recv(buf, sizeof(buf)-1);
		if (recvLen <= 0)
		{
			client.Close();
			delete this;
			return;
		}
		printf("=====recv=============\n%s===================\n", buf);

		// 回应http GET请求
		// 消息头
		string rmsg = "";
		rmsg =	"HTTP/1.1 200 OK\r\n"
				"Server: XHttp\r\n"
				"Content-Type: text/html\r\n"
				"Content-Length: 6\r\n"   // 这里要注意: 浏览器返回多少数据就根据这里的长度来读!
				"\r\n" // 空行
				"0123456789";
		int sendSize = client.Send(rmsg.c_str(), rmsg.size());
		printf("sendsize = %d\n", sendSize);
		printf("============send============\n%s\n================\n", rmsg.c_str());

		client.Close();
		delete this;
	}
	XTcp client;
};

int main(int argc, char** argv)
{
	unsigned short port = 8080;
	if (argc > 1) port = atoi(argv[1]);

	XTcp server;
	server.CreateSocket(); // 这一步可以不用
	server.Bind(port);


	while (true)
	{
		XTcp client = server.Accept();

		XHttpThread *th = new XHttpThread();
		th->client = client;
		std::thread sth(&XHttpThread::Main, th);
		sth.detach();
	}
	server.Close();

	// 客户端测试: telnet 192.168.163.131 8080

	getchar();
	return 0;
}
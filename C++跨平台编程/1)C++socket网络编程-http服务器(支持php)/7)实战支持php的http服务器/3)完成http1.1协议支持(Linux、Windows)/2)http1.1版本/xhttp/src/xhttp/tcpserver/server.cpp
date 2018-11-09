#define _CRT_SECURE_NO_WARNINGS
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
#include <regex>
using namespace std;

class XHttpThread
{
public:
	void Main()
	{
		char buf[10000] = {0};
		while(true) // HTTP1.1 实现一次连接
		{ 
			// 接收http客户端请求
			int recvLen = client.Recv(buf, sizeof(buf)-1);
			if (recvLen <= 0)
			{
				Close();
				return;
			}
			buf[recvLen] = '\0';
			printf("=====recv=============\n%s===================\n", buf);

			//	GET /index.html HTTP/1.1
			//	Host: 192.168.163.131
			//	Connection: keep-alive
			//	Cache-Control: max-age=0
			//	Upgrade-Insecure-Requests: 1
			//	User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36
			//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
			//	Accept-Encoding: gzip, deflate
			//	Accept-Language: zh-CN,zh;q=0.9
		
			string src = buf;
			string pattern("^([A-Z]+?) (.+?) HTTP/1");
			regex reg(pattern);
			smatch mas;
			regex_search(src, mas, reg);
			if (mas.size() == 0)
			{
				printf("%s failed!\n", pattern.c_str());
				Close();
				return;
			}
			string type = mas[1]; // GET
			string path = mas[2]; // /index.html
			if (type != "GET") // 如果type不等于GET直接不处理
			{
				Close();
				return;
			}
		
			if (path == "/")
			{
				path = "/index.html";
			}

			string filepath = "../www" + path;
			FILE *fp = fopen(filepath.c_str(), "rb");
			if (fp == NULL)
			{
				Close();
				return;
			}
			fseek(fp, 0, SEEK_END);
			int filesize = ftell(fp);
			fseek(fp, 0, 0);
			printf("file size is %d\n", filesize);
			char bsize[128] = {0};
			sprintf(bsize, "%d", filesize);


			// 回应http GET请求
			// 消息头
			string rmsg = "";
			rmsg =	"HTTP/1.1 200 OK\r\n"
					"Server: XHttp\r\n"
					"Content-Type: text/html\r\n"
					"Content-Length: " + string(bsize) + "\r\n"   // 这里要注意: 浏览器返回多少数据就根据这里的长度来读!
					"\r\n"; // 空行
					//"0123456789"; // 正文
			int sendSize = client.Send(rmsg.c_str(), rmsg.size());
			printf("sendsize = %d\n", sendSize);
			printf("============send============\n%s\n================\n", rmsg.c_str());

			// 发送正文
			while (true)
			{
				int len = fread(buf, 1,sizeof(buf), fp);
				if (len <= 0) break;
				int re = client.Send(buf, len);
				if (re <= 0) break;
			}
		}
		Close();
	}

	void Close()
	{
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
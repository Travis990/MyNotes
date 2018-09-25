#include "poolsocket.h"
#include "socketutil.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// 线程回调函数
void* pthread_func(void* arg)
{
	static int num = 0;
	void* handle = arg;
	int connfd = -1;
	// 从连接池中取出一条连接
	sckCltPool_getConnet(handle, &connfd);
	for (int i = 0; i < 3; ++i)
	{
		// 通信
		char buf[1024];
		sprintf(buf, "hello, server - %d", num++);
		int ret = sckCltPool_send(handle, connfd, buf, strlen(buf));
		if (ret == Sck_ErrTimeOut)
		{
			printf("发送超时, 重新发送...\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("send 函数调用失败, fd = %d\n", connfd);
			return ret;
		}

		// 接收数据
		int len = -1;
		unsigned char* out = NULL;

		ret = sckCltPool_rev(handle, connfd, &out, &len);
		if (ret == Sck_ErrTimeOut)
		{
			printf("接收超时, 重新接收...\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("recv 函数调用失败\n");
			return ret;
		}
		printf("recv server msg: %s\n", out);
		free(out);
	}
	// 将连接归还连接池
	sckCltPool_putConnet(handle, connfd, 0);
}

int main(int argc, char* argv[])
{
#if 0
	// 初始化套接字
	// 连接服务器
	int connfd = -1;
	sckClient_connect("127.0.0.1", 9999, 5, &connfd);

	// 通信
	while (1)
	{
		const char* str = "hello, server...";
		sckClient_send(connfd, 5, str, strlen(str));
		// 接受数据
		int len = -1;
		unsigned char* out = NULL;
		sckClient_rev(connfd, 5, &out, &len);
		printf("client recv buf: %s\n", out);
		sleep(1);
	}
	// 关闭套接字
	sckServer_close(connfd);
#else
	// 客户端 - 使用连接池版本
	void* handle = NULL;
	SCKClitPoolParam param;
	param.bounds = 10;	// 创建10条连接
	param.connecttime = 5;	// 连接超时为5s
	param.revtime = 5;		// 接收数据超时5s
	param.sendtime = 5;		// 发送数超时5s
	strcpy(param.serverip, "127.0.0.1");
	param.serverport = 9999;
	// 初始化连接池
	sckCltPool_init(&handle, &param);
	// 创建线程
	pthread_t pid[10];
	for (int i = 0; i < 10; ++i)
	{
		pthread_create(&pid[i], NULL, pthread_func, handle);
	}
	// 阻塞等待销毁子线程
	for (int i = 0; i < 10; ++i)
	{
		pthread_join(pid[i], NULL);
	}
	// 销毁客户端连接池
	sckCltPool_destroy(handle);

#endif
#if _WIN32
	printf("Enter any key exit ...\n");
	system("pause");
#endif

	return 0;
		}

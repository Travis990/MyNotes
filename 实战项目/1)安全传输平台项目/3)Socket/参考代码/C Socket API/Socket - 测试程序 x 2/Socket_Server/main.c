#include <stdio.h>
#include <pthread.h>
#include "poolsocket.h"
#include "socketutil.h"

void* pthread_func(void* arg)
{
	int connfd = *(int*)arg;
	// 通信
	while (1)
	{
		// 接收数据
		int outLen = -1;
		unsigned char* outData = NULL;
		printf("*************** connfd = %d\n", connfd);

		int ret = sckServer_rev(connfd, 5, &outData, &outLen);
		if (ret == Sck_ErrPeerClosed)
		{
			printf("客户端关闭连接...\n");
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			printf("data recv timeout, redo...\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("recv func error...\n");
			return ret;
		}
		printf("recv clinet msg: %s\n", outData);
		free(outData);

		// 回发数据
		ret = sckServer_send(connfd, 5, "hello, client...", strlen("hello, client..."));
		if (ret == Sck_ErrTimeOut)
		{
			printf("data recv timeout, redo...");
			continue;
		}
		else if (ret != 0)
		{
			printf("send func error...");
			return ret;
		}
	}
	// 关闭连接
	sckServer_close(connfd);
	// 退出当前子线程
	pthread_exit(NULL);

	return NULL;
}

int main()
{
#if 0
	// 1. 创建套接字 - 监听
	// 2. 监听的套接字绑定本地IP和端口
	// 3. 设置监听
	int lfd = -1;
	sckServer_init(9999, &lfd);
	// 4. 等待并接受连接请求
	int connfd = -1;
	sckServer_accept(lfd, 5, &connfd);
	// 5. 通信
	while (1)
	{
		// 接收数据
		int len = -1;
		unsigned char* out = NULL;
		sckServer_rev(connfd, 5, &out, &len);
		printf("recv buf: %s\n", out);
		free(out);

		// 发送数据
		const char* str = "hello, client=====";
		sckServer_send(connfd, 5, str, strlen(str));
}
	// 6. 关闭套接字
	sckServer_close(connfd);
#else
	int lfd = -1;
	// 初始化监听的套接字
	sckServer_init(9999, &lfd);
	// 等待并接受连接请求
	int i = 0;
	int connfd[1024];
	pthread_t pid[1024];
	while (1)
	{
		int ret = sckServer_accept(lfd, 5, &connfd[i]);
		if (ret == Sck_ErrTimeOut)
		{
			// 跳过本次循环, 继续接收连接请求
			printf("客户端连接超时, ^_^...\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("accept failed\n");
			return ret;
		}
		// 创建一个线程处理连接请求
		printf("===================连接成功=================\n");
		pthread_create(&pid[i], NULL, pthread_func, (void*)&connfd[i++]);
		// 线程分离
		pthread_detach(pid[i]);
	}

	// 销毁
	sckServer_destroy(lfd);
#endif
	printf("hello from Socket!\n");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// 类型
pthread_mutex_t mutex;

// 打印机
void printer(char* str)
{
	while(*str)
	{
		putchar(*str);
		str++;
		fflush(stdout);
		usleep(5000); // 5ms
	}
	printf("\n");
}

// 打印小写字母
void *func1(void *arg)
{
	char *str = "hello";

	// 加锁
	pthread_mutex_lock(&mutex);

	printer(str);

	// 解锁
	pthread_mutex_unlock(&mutex);

	return NULL;
}

// 打印大写字母
void *func2(void *arg)
{
	char *str = "HELLO";

	// 加锁
	pthread_mutex_lock(&mutex);

	printer(str);

	// 解锁
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(void)
{
	int ret = -1;
	pthread_t tid1, tid2;

	// 1. 先初始化mutex  使用默认的属性
	ret = pthread_mutex_init(&mutex, NULL);
	if(0 != ret)
	{
		printf("pthread_mutex_init: %s", strerror(ret));
		goto err0;
	}
	printf("mutex初始化Ok...\n");

	// 创建两个线程
	pthread_create(&tid1, NULL, func1, NULL);
	pthread_create(&tid2, NULL, func2, NULL);

	//2. 在线程处理函数中使用加解锁
	
	// 等待线程终止  回收资源
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	//3. 销毁mutex
	pthread_mutex_destroy(&mutex);

	return 0;
err0:
	return 1;
}

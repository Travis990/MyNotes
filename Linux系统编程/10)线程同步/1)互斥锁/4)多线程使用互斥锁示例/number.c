
// GCC 编译注意: gcc main.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // 线程库

#define SIZE 1000000 // 一百万

pthread_mutex_t mutex; // 初始化互斥锁

int num = 0;

// 线程1处理函数
void* fun1(void *arg)
{
	int i = 0;
	for(i = 0; i < SIZE; i++)
	{
		// 加锁
		pthread_mutex_lock(&mutex);
		
		num++;

		// 解锁
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

// 线程2处理函数
void* fun2(void *arg)
{
	int i = 0;
	for(i = 0; i < SIZE; i++)
	{
		// 加锁
		pthread_mutex_lock(&mutex);
		
		num++;

		// 解锁
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	int ret = -1;
	pthread_t tid1, tid2; // 初始化两个线程

	// 1. 初始化 mutex
	ret = pthread_mutex_init(&mutex, NULL);
	if(0 != ret)
	{
		printf("pthread_mutex_init: %s\n", strerror(ret));
		goto err0;
	}

	// 创建两个线程
	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	// 等待进程退出
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("mian thread:num = %d\n", num);

	// 3 销毁 mutex
	pthread_mutex_destroy(&mutex);

	return 0;
err0:
	return 1;
}

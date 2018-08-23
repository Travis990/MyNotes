#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 1000000

// 两个互斥锁
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int num = 0;

// 线程1处理函数
void* fun1(void *arg)
{
	// 先加锁资源1
	pthread_mutex_lock(&mutex1);
	usleep(100);

	// 加锁资源2
	pthread_mutex_lock(&mutex2);

	// 临界区代码
	printf("线程1执行临界区代码...\n");

	// 解锁资源1
	pthread_mutex_unlock(&mutex1);

	// 解锁资源2
	pthread_mutex_unlock(&mutex2);
	
	return NULL;
}

// 线程2处理函数
void* fun2(void *arg)
{
	// 先加锁资源2
	pthread_mutex_lock(&mutex2);

	// 加锁资源1
	pthread_mutex_lock(&mutex1);

	// 临界区代码
	printf("线程2执行临界区代码...\n");

	// 解锁资源2
	pthread_mutex_unlock(&mutex2);

	// 解锁资源1
	pthread_mutex_unlock(&mutex1);

	return NULL;
}

int main()
{
	int ret = -1;
	pthread_t tid1, tid2; // 两个线程

	// 1. 初始化 nutex1
	ret = pthread_mutex_init(&mutex1, NULL);
	if(0 != ret)
	{
		printf("pthread_mutex_init: %s\n", strerror(ret));
		goto err0;
	}

	// 1. 初始化 mutex2 
	ret = pthread_mutex_init(&mutex2, NULL);
	if(0 != ret)
	{
		printf("pthread_mutex_init: %s\n", strerror(ret));
		goto err0;
	}	

	// 创建两个线程
	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	// 等线程退出
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("main thread:num = %d\n", num);

	// 销毁 mutex 
	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);

	return 0;
err0:
	return 1;
}

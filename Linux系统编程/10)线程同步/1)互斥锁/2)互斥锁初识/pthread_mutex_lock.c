#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//int pthread_mutex_init(pthread_mutex_t *restrict mutex,
//const pthread_mutexattr_t *restrict attr);

int main(void)
{
	int ret = -1;

	pthread_mutex_t mutex;

	// 初始化一个互斥量 第二个参数为空 表示使用默认属性
	ret = pthread_mutex_init(&mutex, NULL);
	if(0 != ret)
	{
		printf("初始化%s\n", strerror(ret));
		goto err0;
	}
	printf("互斥量初始化ok...\n");

	// 加锁
	ret = pthread_mutex_lock(&mutex);
	if(0 != ret)
	{
		printf("pthread_mutex_lock %s\n", strerror(ret));
		goto err1;
	}
	printf("第一次加锁成功...\n");

	//加锁
	//ret = pthread_mutex_lock(&mutex);
	//尝试加锁 如果mutex之前没有上锁 就立即上锁成功. 如果已经上锁, 那么立即出错返回
	ret = pthread_mutex_trylock(&mutex);
	if(0 != ret)
	{
		printf("pthread_mutex_trylock %s\n", strerror(ret));
	}
	else
	{
		printf("第二次加锁成功...\n");
	}

	// 解锁
	ret = pthread_mutex_unlock(&mutex);
	if(0 != ret)
	{
		printf("pthread_mutex_unlock:%s\n", strerror(ret));
		goto err1;
	}
	printf("解锁成功>...\n");

	// 解锁
	ret = pthread_mutex_unlock(&mutex);
	if(0 != ret)
	{
		printf("pthread_mutex_unlock:%s\n", strerror(ret));
		goto err1;
	}
	else
	{
		printf("================== unlock =================\n");
	}

	// 销毁 释放资源
	pthread_mutex_destroy(&mutex);

	return 0;
err1:
	pthread_mutex_destroy(&mutex);
err0:
	return 1;
}

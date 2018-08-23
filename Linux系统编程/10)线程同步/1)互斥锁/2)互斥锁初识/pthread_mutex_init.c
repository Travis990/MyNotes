#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

	// 销毁 释放资源
	pthread_mutex_destroy(&mutex);

	return 0;
err0:
	return 1;
}

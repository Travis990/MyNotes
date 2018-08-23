#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 打印机
void printer(char *str)
{
	while(*str)
	{
		putchar(*str);
		str++;
		fflush(stdout);
		usleep(5000); // 5ms
	}
}

// 打印小写字母
void *func1(void *arg)
{
	char *str = "hello";

	printer(str);

	return NULL;
}

// 打印大写字母
void *func2(void *arg)
{
	char *str = "HELLO";

	printer(str);

	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2;

	// 创建两个线程
	pthread_create(&tid1, NULL, func1, NULL);
	pthread_create(&tid2, NULL, func2, NULL);

	// 等待线程终止  回收资源
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

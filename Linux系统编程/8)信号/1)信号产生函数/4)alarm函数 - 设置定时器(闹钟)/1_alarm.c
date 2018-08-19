#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//unsigned int alarm(unsigned int seconds);

// 闹钟

/*
#include <unistd.h>

unsigned int alarm(unsigned int seconds);
功能：
	设置定时器(闹钟)。在指定seconds后，内核会给当前进程发送14）SIGALRM信号。进程收到该信号，默认动作终止。每个进程都有且只有唯一的一个定时器。
	取消定时器alarm(0)，返回旧闹钟余下秒数。
参数：
	seconds：指定的时间，以秒为单位
返回值：
	返回0或剩余的秒数
*/

int main()
{
	printf("hello world\n");

	alarm(3);

	printf("hello world  3 seconds\n");

	getchar();

	printf("hello world end\n");

	return 0;
}

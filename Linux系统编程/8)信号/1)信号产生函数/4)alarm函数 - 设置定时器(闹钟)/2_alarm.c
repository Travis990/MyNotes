#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	// 定时，与进程状态无关(自然定时法)！就绪、运行、挂起(阻塞、暂停)、终止、僵尸……无论进程处于何种状态，alarm都计时。
	
	int seconds = 0;

	seconds = alarm(5);
	printf("seconds = %d\n", seconds);

	sleep(2);
	seconds = alarm(5);
	printf("seconds = %d\n", seconds);

	while(1);

	return 0;
}

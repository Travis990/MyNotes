#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

/*
#include <sys/time.h>

int setitimer(int which,  const struct itimerval *new_value, struct itimerval *old_value);
功能：
	设置定时器(闹钟)。 可代替alarm函数。精度微秒us，可以实现周期定时。
参数：
	which：指定定时方式
		a) 自然定时：ITIMER_REAL → 14）SIGALRM计算自然时间
		b) 虚拟空间计时(用户空间)：ITIMER_VIRTUAL → 26）SIGVTALRM  只计算进程占用cpu的时间
		c) 运行时计时(用户 + 内核)：ITIMER_PROF → 27）SIGPROF计算占用cpu及执行系统调用的时间
	new_value：struct itimerval, 负责设定timeout时间
		struct itimerval {
			struct timerval it_interval; // 闹钟触发周期
			struct timerval it_value;	 // 闹钟触发时间
		};
		struct timeval {
			long tv_sec; 			// 秒
			long tv_usec; 			// 微秒
		}
		itimerval.it_value：	设定第一次执行function所延迟的秒数 
		itimerval.it_interval：	设定以后每几秒执行function

	old_value： 存放旧的timeout值，一般指定为NULL
返回值：
	成功：0
	失败：-1
*/

void myfunc()
{
	printf("hello\n");
}

int main()
{
	struct itimerval new_value;

	// 定时周期
	new_value.it_interval.tv_sec = 1;
	new_value.it_interval.tv_usec = 0;

	// 第一次触发的时间
	new_value.it_value.tv_sec = 2;
	new_value.it_value.tv_usec = 0;

	signal(SIGALRM, myfunc); // 信号处理
	setitimer(ITIMER_REAL, &new_value, NULL); // 定时器设置

	while(1);

	return 0;
}

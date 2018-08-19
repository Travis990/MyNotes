#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

//int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);



#if 0
struct itimerval {
    struct timeval it_interval; /* Interval for periodic timer */
    struct timeval it_value;    /* Time until next expiration */
};

struct timeval {
    time_t      tv_sec;         /* seconds */
    suseconds_t tv_usec;        /* microseconds */
};

#endif

// 信号处理函数
void func1(int signo)
{
	printf("捕捉到信号%d\n", signo);
}

int main()
{
	struct itimerval t = {
		.it_interval = {  // 以后执行周期时间
			.tv_sec = 1,
			.tv_usec = 0
		},

		.it_value = {  // 第一次执行时间
			.tv_sec = 3,
			.tv_usec = 0
		}
	};

	// 信号捕捉
	signal(SIGALRM, func1);
	
	// 设置定时器
	setitimer(ITIMER_REAL, &t, NULL);

	printf("输入任意键继续...\n");

	getchar();	


	return 0;
}

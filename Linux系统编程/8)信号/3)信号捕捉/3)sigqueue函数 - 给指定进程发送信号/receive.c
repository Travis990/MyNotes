#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 信号处理回调函数
void signal_handler(int signum, siginfo_t *info, void *ptr)
{
	printf("signum = %d\n", signum); // 信号编号
	printf("info->si_pid = %d\n", info->si_pid); // 对方的进程号
	printf("info->si_sigval = %d\n", info->si_value.sival_int); // 对方传递过来的信息
}

int main()
{
	struct sigaction act, oact;

	act.sa_sigaction = signal_handler; //指定信号处理回调函数
	sigemptyset(&act.sa_mask); // 阻塞集为空
	act.sa_flags = SA_SIGINFO; // 指定调用 signal_handler

	// 注册信号 SIGINT
	sigaction(SIGINT, &act, &oact);

	while (1)
	{
		printf("pid is %d\n", getpid()); // 进程号

		pause(); // 捕获信号，此函数会阻塞
	}

	return 0;
}

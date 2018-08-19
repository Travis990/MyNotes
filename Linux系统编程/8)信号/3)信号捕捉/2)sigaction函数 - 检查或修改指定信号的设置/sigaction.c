#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
功能：
	检查或修改指定信号的设置（或同时执行这两种操作）。
返回值：
	成功：0
	失败：-1
*/

/*
//struct sigaction结构体：
struct sigaction {
	void(*sa_handler)(int); //旧的信号处理函数指针
	void(*sa_sigaction)(int, siginfo_t *, void *); //新的信号处理函数指针
	sigset_t   sa_mask; 	 //信号阻塞集
	int        sa_flags;	 //信号处理的方式
	void(*sa_restorer)(void); //已弃用
};

// 信号处理函数:
void(*sa_sigaction)(int signum, siginfo_t *info, void *context);
参数说明：
	signum：信号的编号。
	info：记录信号发送进程信息的结构体。
	context：可以赋给指向 ucontext_t 类型的一个对象的指针，以引用在传递信号时被中断的接收进程或线程的上下文。

*/

void myfunc(int sig)
{
	printf("hello signal: %d\n", sig);
	sleep(5);
	printf("wake up .....\n");
}

int main()
{
	// 注册信号捕捉函数
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = myfunc;
	// 设置临时屏蔽的信号
	sigemptyset(&act.sa_mask); // 清空
	// Ctrl + 反斜杠
	sigaddset(&act.sa_mask, SIGQUIT);
	
	sigaction(SIGINT, &act, NULL); // 注册信号

	while(1);

	return 0;
}

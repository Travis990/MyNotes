#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
信号处理方式:
	一个进程收到一个信号的时候，可以用如下方法进行处理：
	1）执行系统默认动作
	对大多数信号来说，系统默认动作是用来终止该进程。
	2）忽略此信号(丢弃)
	接收到此信号后没有任何动作。
	3）执行自定义信号处理函数(捕获)
	用用户定义的信号处理函数处理该信号。
【注意】：SIGKILL 和 SIGSTOP 不能更改信号的处理方式，因为它们向用户提供了一种使进程终止的可靠方法。


#include <signal.h>

typedef void(*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
返回值：
	成功：第一次返回 NULL，下一次返回此信号上一次注册的信号处理函数的地址。如果需要使用此返回值，必须在前面先声明此函数指针的类型。
	失败：返回 SIG_ERR
*/

// 由ANSI定义，由于历史原因在不同版本的Unix和不同版本的Linux中可能有不同的行为。因此应该尽量避免使用signal()函数，取而代之使用sigaction函数。

void signal_handler(int signo)
{
	if(signo == SIGINT)
	{
		printf("recv SIGINT\n");
	}
	else if(signo == SIGQUIT)
	{
		printf("recv SIGQUIT\n");
	}
}

int main()
{
	printf("wait for SIGINT OR SIGQUIT\n");

	/* SIGINT: Ctrl+c ; SIGQUIT: Ctrl+\ */
	// 信号注册函数
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	while(1); // 不让程序结束

	return 0;
}

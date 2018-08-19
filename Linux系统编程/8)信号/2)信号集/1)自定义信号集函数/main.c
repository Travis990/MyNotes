#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// PCB中有两个非常重要的信号集:
// 1. 阻塞信号集
// 2. 未决信号集

// 这两个信号集都是内核使用位图机制来实现的。但操作系统不允许我们直接对其进行位操作。而需自定义另外一个集合，借助信号集操作函数来对PCB中的这两个信号集进行修改。

/*
#include <signal.h>  

int sigemptyset(sigset_t *set);       //将set集合置空
int sigfillset(sigset_t *set)；		    //将所有信号加入set集合
int sigaddset(sigset_t *set, int signo);  //将signo信号加入到set集合
int sigdelset(sigset_t *set, int signo);   //从set集合中移除signo信号
int sigismember(const sigset_t *set, int signo); //判断信号是否存在

*/

// 自定义信号集函数

int main()
{
	sigset_t set; // 定义一个信号集变量
	int ret = 0;

	sigemptyset(&set); // 清空信号集的内容

	// 判断 SIGINT 是否在信号集 set 里
	// 在返回 1, 不在返回 0
	
	ret = sigismember(&set, SIGINT);
	if(ret == 0)
	{
		printf("SIGINT is not a member of set \nret = %d\n", ret);
	}

	sigaddset(&set, SIGINT); // 把 SIGINT 添加到信号集 set
	sigaddset(&set, SIGQUIT); // 把 SIGQUIT 添加到信号集 set

	// 判断 SIGINT 是否在信号集 set 里
	// 在返回 1, 不在返回 0
	ret = sigismember(&set ,SIGINT);
	if(ret == 1)
	{
		printf("SIGINT is a member of set \nret = %d\n", ret);
	}

	sigdelset(&set, SIGQUIT); // 把 SIGQUIT 从信号集 set 移除

	// 判断 SIGQUIT 是否在信号集 set 里
	// 在返回 1, 不在返回 0
	ret = sigismember(&set, SIGQUIT);
	if(ret == 0)
	{
		printf("SIGQUIT is not a member of set \nret = %d\n", ret);
	}

	return 0;
}

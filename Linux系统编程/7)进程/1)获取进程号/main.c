#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

//获取调用进程进程号
//pid_t getpid(void);
//获取调用进程的父进程号
//pid_t getppid(void);

int main()
{
	printf("进程号: %d\n", getpid());

	printf("父进程号: %d\n", getpid());

	//获取当前进程的进程组号
	printf("当前进程组号: %d\n", getpgid(getpid()));	

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = -1;

	// 创建一个子进程
	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		goto err0;
	}

	// 子进程
	if(0 == pid)
	{
		while(1)
		{
			printf("I am Child process pid: %d\n", getpid());
			sleep(1);
		}
	}
	else
	{
		// 父进程
		while(1)
		{
			printf("I am parent process pid: %d cpid: %d\n", getpid(), pid);
			sleep(1);
		}
	}

	return 0;
err0:
	return 1;
}

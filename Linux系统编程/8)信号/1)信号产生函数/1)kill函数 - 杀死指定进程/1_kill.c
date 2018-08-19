#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	int i = 0;
	pid_t pid = -1;

	// 创建一个进程
	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		goto err0;
	}

	// 子进程
	if(0 == pid)
	{
		while(1)
		{
			printf("hello world %d\n", i++);
			sleep(1);
		}
		exit(0);
	}
	else
	{
		// 父进程
		printf("parent process sleep 3 seconds\n");
		sleep(3);
		kill(pid, SIGKILL);
		printf("子进程被父进程kill掉了>..\n");
	}

	return 0;
err0:
	return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		int i = 0;
		for(i = 0; i < 5; i++)
		{
			printf("in son process\n");
			sleep(1);
		}
	}
	else
	{ // 父进程
		printf("in father process\n");
		sleep(2);
		printf("kill sub process now\n");
		kill(pid, SIGINT);
	}

	return 0;
}

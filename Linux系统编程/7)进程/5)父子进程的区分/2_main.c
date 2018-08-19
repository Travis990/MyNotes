#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork"); // 没有创建成功
	}

	if(0 == pid)
	{ // 子进程
		while(1)
		{
			printf("I am son\n");
			sleep(1);
		}
	}
	else if(pid > 0)
	{
		while(1)
		{
			printf("I am father\n");
			sleep(1);
		}
	}
	

	return 0;
}

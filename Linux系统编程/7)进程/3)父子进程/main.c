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
		printf("我是子进程...\n");
	}
	else
	{
		printf("我是父进程...\n");
	}

	printf("Hello world!\n");

	return 0;
err0:
	return 1;
}

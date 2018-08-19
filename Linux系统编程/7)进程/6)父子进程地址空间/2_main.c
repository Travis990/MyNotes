#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid = -1;

	int *p = NULL;

	// 分配空间
	p = malloc(sizeof(int));
	if(NULL == p)
	{
		printf("malloc failed...\n");
		goto err0;
	}
	memset(p, 0 ,sizeof(int));

	*p = 88;

	// 创建一个子进程
	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		goto err0;
	}

	if(0 == pid)
	{
		printf("child process *p: %d\n", *p);
		printf("child p = %p\n", p);
	}
	else
	{
		printf("parent process *p: %d\n", *p);
		printf("parent p = %p\n", p);
	}

	free(p);
	p = NULL;

	return 0;
err0:
	return 1;
}

// Linux下检查内存泄漏方法: # valgrind ./a.out

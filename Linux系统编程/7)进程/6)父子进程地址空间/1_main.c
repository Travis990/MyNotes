#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int a = 10; // 全局变量

int main()
{
	int b = 20; // 局部变量
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{ // 没有创建成功
		perror("fork");
	}

	if(0 == pid)
	{ // 子进程
		a = 111;
		b = 222;  // 子进程修改其值
		printf("son: a = %d, b = %d\n", a, b);
		printf("son的地址: a = %p , b = %p\n", &a ,&b);
	}
	else if(pid > 0)
	{ // 父进程
		sleep(1); // 保证子进程先运行
		printf("father: a = %d, b = %d\n", a, b);
		printf("father的地址: a = %p , b = %p\n", &a ,&b);
	}

	// 切记: 父子进程各自的地址空间是独立的!

	return 0;
}

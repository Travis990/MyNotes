#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("hello world\n");
	
	// 功能：给自己发送异常终止信号 6) SIGABRT，并产生core文件，等价于kill(getpid(), SIGABRT);
	abort();

	printf("hello end\n");

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	printf("hello world\n");
	
	// 自己给自己发送一个信号
	// 等价于kill(getpid(), SIGKILL);
	
	raise(SIGKILL);// 进程自杀

	printf("hello end\n");

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
#include <unistd.h>

char *ttyname(int fd);
功能：由文件描述符查出对应的文件名
参数：
	fd：文件描述符
返回值：
	成功：终端名
	失败：NULL
*/

int main()
{
	printf("fd 0: %s\n", ttyname(0));
	printf("fd 1: %s\n", ttyname(1));
	printf("fd 2: %s\n", ttyname(2));

	
	printf("%s\n", ttyname(STDIN_FILENO));
	printf("%s\n", ttyname(STDOUT_FILENO));
	printf("%s\n", ttyname(STDERR_FILENO));

	return 0;
}

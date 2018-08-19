#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 128

//char *getcwd(char *buf, size_t size);

int main(void)
{
	char buf[SIZE];
	memset(buf, 0, SIZE);
	//获取当前工作路径  绝对路径
	if(NULL == getcwd(buf , SIZE))
	{
		perror("getcwd");
		goto err0;
	}

	printf("buf: %s\n",buf);

	return 0;
err0:
	return 1;
}

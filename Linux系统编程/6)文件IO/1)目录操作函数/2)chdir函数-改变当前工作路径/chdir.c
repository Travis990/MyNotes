#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>

#define SIZE 128

int main()
{
	char buf[SIZE];

	//1. 先获取当前工作路径
	memset(buf, 0, SIZE);
	if(NULL == getcwd(buf, SIZE))
	{
		perror("getcwd");
		goto err0;
	}

	printf("buf: %s\n", buf);

	//2. 改变当前工作路径
	if(-1 == chdir("/tmp"))
	{
		perror("chdir");
		goto err0;
	}
	printf("改变当前工作路径成功...\n");
	

	//3. 获取当前工作路径 测试
	memset(buf, 0, SIZE);
	if(NULL == getcwd(buf, SIZE))
	{
		perror("getcwd");
		goto err0;
	}

	printf("buf: %s\n", buf);

	return 0;

err0:
	return 1;
}

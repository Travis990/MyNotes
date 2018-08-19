#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <sys/types.h>
#include <dirent.h>

//打开目录
//DIR *opendir(const char *name);

int main(void)
{
	DIR *dir = NULL;

	//打开目录
	dir = opendir("./test");
	if(NULL == dir)
	{
		perror("opendir");
		goto err0;
	}

	printf("open directory successfully....\n");

	//关闭目录
	closedir(dir);

	return 0;
err0:
	return 1;
}

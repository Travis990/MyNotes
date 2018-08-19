#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <sys/types.h>
#include <dirent.h>

//打开目录
//DIR *opendir(const char *name);
//struct dirent *readdir(DIR *dirp);


int main(void)
{
	DIR *dir = NULL;
	struct dirent *d = NULL;

	//1. 打开目录
	dir = opendir("./test");
	if(NULL == dir)
	{
		perror("opendir");
		goto err0;
	}

	printf("open directory successfully....\n");

	//2. 读取目录内容
	d = readdir(dir);
	if(NULL == d)
	{
		perror("readdir");
		goto err1;
	}

	printf("inode:%ld d_reclen: %d  d_type: %d d_name: %s\n", d->d_ino, d->d_reclen, d->d_type, d->d_name);

	//3. 关闭目录
    closedir(dir);

	return 0;
err0:
	return 1;
err1:
	closedir(dir);
}

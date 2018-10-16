#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>

#include "make_log.h" //日志头文件
#define SIZE 512

#define TEST_LOG_MODULE "test"
#define FDFS_LOG_PROC   "fdfs"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		 printf("usage ./a.out file_path\n");
		return -1;
	}
	
	char *filename = argv[1]; //文件名
	
	pid_t pid; //进程号
	int fd[2]; //无名管道文件描述符
	char buf[SIZE] = {0};
	
	//无名管道的创建
	if( pipe(fd) < 0 )
	{
		perror("pipe");
		return -2;
	}
	
	//创建进程
	pid = fork(); 
	if(pid < 0) //进程创建失败
	{
		perror("fork");
		return -3;
	}
	else if(pid == 0) //子进程
	{
		//关闭读端
		close(fd[0]);
		
		//将标准输出 重定向 写管道
		dup2(fd[1], STDOUT_FILENO); //dup2(fd[1], 1);
		
		//通过execlp执行fdfs_upload_file
		execlp("fdfs_upload_file", "fdfs_upload_file", "/etc/fdfs/client.conf", filename, NULL);
		
	}
	else //父进程
	{
		//关闭写端
		close(fd[1]);
		
		//等待子进程结束，回收其资源
		wait(NULL);
		
		//从管道中去读数据
		read(fd[0], buf, sizeof(buf) );
		
		//将结果导入log中
		LOG(TEST_LOG_MODULE, FDFS_LOG_PROC, "get_file_id[%s]", buf);
	}
	
  
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	int ret = -1;
	pid_t pid = -1;
	// 1. 创建子进程 父进程退出
	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		goto err0;
	}

	// 父进程退出 
	if(pid > 0)
	{
		exit(0);
	}

	// 2. 子进程创建一个新的会话
	pid = setsid();
	if(-1 == pid)
	{
		perror("setsid");
		goto err0;
	}

	// 3. 设置权限掩码 umask
	umask(0);

	// 4. 改变进程工作目录
	ret = chdir("/home/notes");
	if(-1 == ret)
	{
		perror("chdir");
		goto err0;
	}

	// 5. 关闭不需要的文件描述符
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// 6. 执行核心工作
	while(1)
	{
		system("echo \"hello world\" >> /tmp/txt");
		sleep(1);
	}
	
	// 终端执行下命令可观察效果
	// # tail -f /tmp/txt      

	return 0;
err0:
	return 1;
}

/* ************************************************************************
 *       Filename:  02_process_tcp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月24日 17时11分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "wrap.h"
void free_process(int sig)
{
	pid_t pid;
	while(1)
	{
		pid = waitpid(-1,NULL,WNOHANG);//当子进程退出回收资源,如果现在没有
	//子进程退出,则马上返回
		if(pid <= 0)//出错或则没有子进程退出 pid == 0
		{
			break;
		}
		else
		{
		
			printf("process pid=%d exit\n",pid);
		}
	}

}
int main(int argc, char *argv[])
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,NULL);

	//创建套接字
	//绑定
	int lfd = tcp4bind(8080,NULL);
	//监听
	listen(lfd,128);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	char ip[INET_ADDRSTRLEN]={0};
	pid_t pid;
	while(1)
	{
		bzero(&cliaddr,sizeof(cliaddr));
	//	sleep(1);
		printf("lfd =%d\n",lfd);
		//提取
		int cfd =Accept(lfd,(struct sockaddr *)&cliaddr,&len);
		printf("new client ip=%s port =%d\n",inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,
					ip,INET_ADDRSTRLEN),ntohs(cliaddr.sin_port));
		//创建子进程
		pid = fork();
		if(pid < 0)
			perror("");
		else if( 0 == pid)//子进程
		{
			close(lfd);//关闭监听套接字
			int ret=0;
			char recv_buf[1024]="";
			while(1)
			{
				ret = Read(cfd,recv_buf,sizeof(recv_buf));
				if(ret < 0)
				{
					perror("");
					break;
				}
				else if( 0 == ret )
				{
					
					printf("client close\n");
					break;
				}
				else
				{
				
					printf("%s\n",recv_buf);
					Write(cfd,recv_buf,ret);
				}
			}
			printf("close#########################\n");
			close(cfd);//关闭已连接套接字
			exit(0);
		
		}
		else//父进程
		{
		
			close(cfd);
			struct sigaction act;
			act.sa_handler =free_process;
			act.sa_flags = 0;
			sigemptyset(&act.sa_mask);
			sigaction(SIGCHLD,&act,NULL);
			sigprocmask(SIG_UNBLOCK,&set,NULL);

			//回收资源
		}
	}
	return 0;
}



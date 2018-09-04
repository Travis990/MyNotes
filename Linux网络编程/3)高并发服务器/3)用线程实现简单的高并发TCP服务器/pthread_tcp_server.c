/* ************************************************************************
 *       Filename:  03_pthread_tcp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月26日 10时29分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include "wrap.h"
void* pthread_call(void *arg);
typedef struct _info
{
	int cfd;
	struct sockaddr_in cliaddr;
}INFO;
int main(int argc, char *argv[])
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);	
	if(argc != 2 )
	{
		printf("argc < 2 ?????");
		return 0;
	}
	unsigned port = atoi(argv[1]);
	printf("port=%d\n",port);
	//创建套接字,绑定
	int lfd = tcp4bind(port,NULL);
	//监听
	//socklen_t len1 =1;
//	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&len1,sizeof(len1));
	listen(lfd,128);
	//while()提取链接
	struct sockaddr_in cliaddr;
	socklen_t len =sizeof(cliaddr);
	pthread_t pthid;
	INFO *info=NULL;
	while(1)
	{
		int cfd = Accept(lfd,(struct sockaddr*)&cliaddr,&len);
		info = (INFO *)malloc(sizeof(INFO));
		info->cfd = cfd;
		info->cliaddr = cliaddr;
		pthread_create(&pthid,&attr,pthread_call,info);	//创建线程,回调函数服务客户端
	}
	


	return 0;
}

void* pthread_call(void *arg)
{
	INFO *info = (INFO *)arg;
	char buf[1024]="";
	int ret =0;
	char ip[16]="";
	printf("%s %d\n",inet_ntop(AF_INET,&info->cliaddr.sin_addr.s_addr,ip,16),
			ntohs(info->cliaddr.sin_port));
	while(1)
	{
		ret = Read(info->cfd,buf,sizeof(buf));
		if(ret < 0)
		{
			perror("");	
			break;
		}
		else if(0 == ret )
		{
			printf("client close\n");
			break;
		}
		else 
		{
			printf("%s\n",buf);
			Write(info->cfd,buf,ret);
		}
	}
	close(info->cfd);
	free(info);


}

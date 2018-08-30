/* ************************************************************************
 *       Filename:  unix_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月29日 16时53分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{

	unlink("sock.s");//删除文件
	//创建本地套接字
	int sfd = socket(AF_UNIX,SOCK_STREAM,0);
	//绑定
	struct sockaddr_un seraddr;
	bzero(&seraddr,sizeof(seraddr));
	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path ,"sock.s");
	bind(sfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	//监听
	listen(sfd,128);
	//提取
	
	struct sockaddr_un cliaddr;
	bzero(&cliaddr,sizeof(cliaddr));
	socklen_t len = sizeof(cliaddr);
	int cfd = accept(sfd,(struct sockaddr *)&cliaddr,&len);
	printf("%s\n",cliaddr.sun_path);
	//读写
	while(1)
	{
		char buf[1024]="";
		int n  = read(cfd,buf,sizeof(buf));
		if(n < 0)
		{
			perror("");
			break;
		}
		else if(n == 0)
		{
			printf("client close\n");
			break;
		}
		else
		{
			
			printf("%s\n",buf);
			write(cfd,buf,n);
			
		}
	
	}
	//关闭
	return 0;
}



/* ************************************************************************
 *       Filename:  unix_client.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月29日 17时13分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	//	创建本地套接字
	int cfd =	socket(AF_UNIX,SOCK_STREAM,0);
	//绑定
	struct sockaddr_un cliaddr;
	cliaddr.sun_family = AF_UNIX;
	strcpy(cliaddr.sun_path,"sock.c");
	bind(cfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	//连接
	struct sockaddr_un seraddr;
	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path,"sock.s");
	connect(cfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	//读写
	while(1)
	{
		char buf[1500]="";

		int n = read(STDIN_FILENO,buf,sizeof(buf));
		write(cfd,buf,n);
		memset(buf,0x00,sizeof(buf));
		read(cfd,buf,sizeof(buf));
		printf("read = %s\n",buf);
	
	
	}
	//关闭



	return 0;
}



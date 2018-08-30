/* ************************************************************************
 *       Filename:  udp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月29日 16时00分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	//创建套接字
	int sfd = socket(AF_INET,SOCK_DGRAM,0);
	//绑定
	struct sockaddr_in myaddr;
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family =AF_INET;
	myaddr.sin_port = htons(8889);
	myaddr.sin_addr.s_addr = INADDR_ANY;
	bind(sfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
	//读写
	while(1)
	{
		struct sockaddr_in cliaddr;
		socklen_t len = sizeof(cliaddr);
		char buf[1024]="";
		//收数据
		int n = recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&len);
		if(n < 0)
		{
			perror("");
			break;
		}
		else
		{
			printf("%s\n",buf);
			sendto(sfd,buf,n,0,(struct sockaddr *)&cliaddr,len);
		
		}
	
	}
	//关闭
		







	return 0;
}



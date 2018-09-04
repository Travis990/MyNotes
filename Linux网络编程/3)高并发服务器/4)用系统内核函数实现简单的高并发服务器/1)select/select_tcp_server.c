/* ************************************************************************
 *       Filename:  04_select_tcp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月26日 16时54分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "wrap.h"
int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("argc < 2\n");
		return 0;
	}
	unsigned short port = atoi(argv[1]);
	int lfd = tcp4bind(port,NULL);//创建套接字,绑定
	listen(lfd,128);//监听
	int max = lfd;
	fd_set oldset,rset;
	FD_ZERO(&oldset);
	FD_ZERO(&rset);
	FD_SET(lfd,&oldset);
	int fd_size=0;
//	int max = lfd;
	while(1)
	{
		rset = oldset;
		fd_size = select(max+1,&rset,NULL,NULL,NULL);//永久等待监听rset集合中文件描述符的变化
		if(fd_size <= 0)//如果监听失败,或者没有监听到文件描述符变化,则从新开始监听
		{
			continue;
		}
		else
		{
			if(FD_ISSET(lfd,&rset))//如果lfd在rset集合中,则lfd变化了(有新的连接请求)
			{
				struct sockaddr_in cliaddr;
				socklen_t len = sizeof(cliaddr);
				char ip[16]="";
				int cfd = Accept(lfd,(struct sockaddr*)&cliaddr,&len);//提取新的连接,返回以连接套接字
				printf("ip = %s  port =%d\n",inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,ip,16),
						ntohs(cliaddr.sin_port));
				//提取的以连接套接字下一次需要监听
				FD_SET(cfd,&oldset);
				if(cfd > max)//如果新的已连接套接字大于原来最大文件描述符,则cfd为最大的
				max = cfd;
				if( --fd_size == 0)//如果fd_size值等于1,只监听到一个文件描述符变化,则处理完毕
					continue;

				
			}
			//有cfd变化
			int i=0;
			for(i = lfd+1;i<=max;i++)//从lfd+1开始遍历rset集合
			{
				if(FD_ISSET(i,&rset))//如果文件描述符i在集合中则返回大于0
				{
					char buf[1024]="";
					int cont = Read(i,buf,sizeof(buf));
					if(cont <= 0)//出错或则客户端关闭
					{

						printf("err or client close\n");
						FD_CLR(i,&oldset);//将已连接套接字i从oldset集合中删除
					}
					else {
					
						printf("%s\n",buf);
						Write(i,buf,cont);
					}


				
				}
			}
		
		
		
		
		
		}
	

	
	}



	return 0;
}


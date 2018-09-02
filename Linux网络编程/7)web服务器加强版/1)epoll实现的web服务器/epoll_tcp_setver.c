/* ************************************************************************
 *       Filename:  epoll_tcp_setver.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月27日 15时04分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "wrap.h"

int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		printf("argc <2 !!!!");
		return 0;
	}
	unsigned short port = atoi(argv[1]);
	//创建套接字,绑定
	int lfd = tcp4bind(port,NULL);
	//监听
	listen(lfd,128);
	//创建树
	int epfd = epoll_create(1);
	//lfd上树
	struct epoll_event ev,evs[1024];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;//监听lfd的读事件
	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);//将ev节点上树监听
	//监听
	int nready=0;
	while(1)
	{
		nready = epoll_wait(epfd,evs,1024,-1);//监听
		printf("epoll ok\n");
		if(nready < 0)
		{
			perror("");
			break;
		}
		else if(nready == 0)
		{
			continue;
		}
		else//监听到了文件描述符变化
		{
			for(int i=0;i<nready;i++)//处理监听到的文件描述符
			{
				if(evs[i].data.fd  == lfd && evs[i].events & EPOLLIN)//如果这个数组元素中的fd是lfd并且监听到的是读事件,有新的连接
				{
					struct sockaddr_in cliaddr;
					socklen_t len = sizeof(cliaddr);
					int cfd = 0;
					cfd = Accept(lfd,(struct sockaddr *)&cliaddr,&len);//提取新的连接
					ev.data.fd = cfd;
					ev.events = EPOLLIN | EPOLLET;//设置监听cfd的边沿触发
					//设置cfd为非阻塞
					int flag = fcntl(cfd,F_GETFL);
					flag |= O_NONBLOCK;
					fcntl(cfd,F_SETFL,flag);
					epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);//将cfd上树
					
				
				}
				else if( evs[i].events & EPOLLIN)//否则就是cfd变化,确认一下是否是cfd的读事件发生
				{
					while(1)
					{
						char buf[5]="";
						int cont = Read(evs[i].data.fd,buf,sizeof(buf)-1);//读取客户端发送过来的消息
						if(cont <0)//如果对方关闭或者出错
						{
							//cont<0有两种情况,出错,缓冲区读干净了
							//
							if(errno == EAGAIN)//如果errno的值设置为EAGAIN 这个宏,代表缓冲区无数据了
							break;
								close(evs[i].data.fd);//关闭cfd套接字
							//下树
							epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
							break;

						}
						else if(cont == 0)
						{
							printf("client close\n");
								close(evs[i].data.fd);//关闭cfd套接字
							//下树
							epoll_ctl(epfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
							break;
							
						}
						else
						{
							printf("%s\n",buf);
							Write(evs[i].data.fd,buf,cont);//写回数据给客户端

						}
					}
				
				}
			}
		
		}
	

	
	}




	return 0;
}


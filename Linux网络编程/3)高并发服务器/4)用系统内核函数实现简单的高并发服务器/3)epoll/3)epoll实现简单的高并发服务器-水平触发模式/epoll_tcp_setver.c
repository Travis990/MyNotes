#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>

#include <string.h>
#include <stdlib.h>
#include "wrap.h"

int main(int argc, char** argv)
{
	if( argc < 2 )
	{
		printf("argc < 2 !!!");
		return 0;
	}
	unsigned short port = atoi(argv[1]);
	// 创建套接字,绑定
	int lfd = tcp4bind(port, NULL);
	// 监听
	listen(lfd, 128);
	// 创建树
	int epfd = epoll_create(1);
	// lfd上树
	struct epoll_event ev, evs[1024];
	ev.data.fd = lfd;
	ev.events = EPOLLIN; // 监听lfd的读事件
	epoll_ctl(epfd,EPOLL_CTL_ADD, lfd, &ev); // 将ev节点上树监听
	// 循环监听
	int nready = 0;
	while(1)
	{
		nready = epoll_wait(epfd, evs, 1024, -1); // -1 永久监听
		if( nready < 0 )
		{
			perror("epoll_wait");
			break;
		}
		else if( nready == 0 )
		{
			continue;
		}
		else // 监听到了文件描述符变化
		{
			for( int i = 0; i < nready; i++ ) // 处理监听到的文件描述符
			{
				if( evs[i].data.fd == lfd && evs[i].events & EPOLLIN ) // 如果这个数组元素中的fd是lfd并且监听到的是读事件,有新的连接
				{
					struct sockaddr_in cliaddr;
					socklen_t len = sizeof(cliaddr);
					int cfd = 0;
					cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len); // 提取新的连接
					ev.data.fd = cfd;
					ev.events = EPOLLIN;
					epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev); // 将cfd上树
				}
				else if( evs[i].events & EPOLLIN ) // 否则就是cfd变化,确认一下是否是cfd的读事件发生
				{
					char buf[1500] = "";
					int cont = Read(evs[i].data.fd, buf, sizeof(buf)); // 读取客户端发送过来的消息
					if( cont <= 0 ) // 如果对方关闭或者出错
					{
						close(evs[i].data.fd); // 关闭cfd套接字
						// 下树
						epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
					}
					else
					{
						printf("%s\n", buf);
						Write(evs[i].data.fd, buf, cont); // 写回数据给客户端
					}
				}
			}
		}
	}

	return 0;
}

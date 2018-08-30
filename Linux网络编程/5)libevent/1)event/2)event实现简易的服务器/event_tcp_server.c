/* ************************************************************************
 *       Filename:  event_tcp_server.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年08月30日 11时18分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>

#include "wrap.h"

#include <event.h>
struct event *ev;
//cfd变化了,回调函数,读客户端发来的数据,然后发送回去
void cfdcb(int cfd,short event,void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	char buf[1024]="";
	int cont = Read(cfd,buf,sizeof(buf));
	if(cont <= 0)
	{
		
		printf("close or err\n");
		//下树
		event_del(ev);
	}
	else
	{
		
		printf("%s\n",buf);
		Write(cfd,buf,cont);
	}
	
}
//lfd回调函数应该做什么事? 
void lfdcb(int lfd,short event,void *arg)
{
	struct event_base *base = (struct event_base *)arg;
		int cfd = Accept(lfd,NULL,NULL);
	//初始化上树节点
	//ev永远是最后一个上树节点的地址
	ev = event_new(base,cfd,EV_READ | EV_PERSIST,cfdcb,base);
	//上树监听
	event_add(ev,NULL);

}
int main(int argc, char *argv[])
{

	//创建套接字
	int lfd = tcp4bind(8888,NULL);
	//绑定
	//监听
	listen(lfd,128);
	//创建event_base结构体
	struct event_base *base = event_base_new();
	//初始化上树节点
	struct event *ev = event_new(base,lfd,EV_READ | EV_PERSIST,lfdcb,base);
	//上树监听
	event_add(ev,NULL);
	//循环监听

	event_base_dispatch(base);//循环监听,阻塞,类似于while(1)){epoll_wait}  阻塞
	//扫尾释放
	event_base_free(base);

	return 0;
}



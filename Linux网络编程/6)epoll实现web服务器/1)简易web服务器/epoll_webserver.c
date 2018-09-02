#include <stdio.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include "wrap.h"
#include <sys/stat.h>

#define SITE_ROOT "/home/wwwroot"     // 网站根目录

#define PORT 80
#define EVENT_MAX 1024
void read_info(struct epoll_event *ev, int epfd)
{
	char buf[1024] = "";
	char num[1024] = "";
	int n = Readline(ev->data.fd, buf, sizeof(buf));  // 读取请求行
	if( n == 0 )
	{
		printf("client close \n");
		epoll_ctl(epfd, EPOLL_CTL_DEL, ev->data.fd, ev);
	}
	printf("[%s]\n", buf);
	while( (n = Readline(ev->data.fd, num, sizeof(num))) > 0 ); // 将请求内容读干净
	printf("read ok \n");
	//解析请求行数据
	char method[10]="";   //  GET or POST
	char path[1024]="";   //  /index.html
	char protocol[20]=""; //  HTTP/1.1
	sscanf(buf,"%[^ ] %[^ ] %[^ ]\r\n", method, path, protocol);
	printf("%s", buf);
	
	// 获得当前工作目录
	char cur_filepath[1024] = SITE_ROOT;
	strcat(cur_filepath, path);

	// 判断文件 or 目录, 如果不存在文件再切换目录,如果目录也不存在 返回404
	struct stat cur_fileinfo;
	bzero(&cur_fileinfo, sizeof(cur_fileinfo));
	stat(cur_filepath, &cur_fileinfo);
	
	
	printf(" cur_filepath:%s\n", cur_filepath);
	int ret = chdir(cur_filepath);
	if(-1 == ret)
	{
		// 返回 404
		send(ev->data.fd, "404", strlen("404"), 0);
		goto _close;
	}

	// 拼接反馈信息
	char recv_content[1024]="";
	char cur_cwd[1024] = "";
	getcwd(cur_cwd, sizeof(cur_cwd));
	sprintf(recv_content, "path:%s ret:%d\n", cur_cwd, ret);
	
	// 将请求内容反馈给用户浏览器
	send(ev->data.fd, recv_content, strlen(recv_content), 0);

_close:
	// 关闭客户端连接
	close(ev->data.fd);
	epoll_ctl(epfd, EPOLL_CTL_DEL, ev->data.fd, ev);
	
	//得到请求的文件   stat()
	//判断请求的文件在不在web-http目录
	//如果在发送这个文件  先发送消息头,在发送文件
	//如果不在发送error.html文件,先发送消息头,在发送error,html文件
}

int main()
{
	// 创建套接字,绑定
	int lfd = tcp4bind(PORT, NULL);
	
	// 监听
	Listen(lfd, 128);

	// 创建树
	int epfd = epoll_create(1);

	// lfd上树
	struct epoll_event ev, evs[EVENT_MAX];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev); // 将lfd节点上树
	
	// 循环监听
	int nready = 0;
	while(1)
	{
		nready = epoll_wait(epfd, evs, EVENT_MAX, -1); // -1永久监听
		if( nready > 0 )
		{
			for( int i = 0; i < nready; i++ ) // 循环遍历已监听到的节点
			{
				// 如果evs[i]这个节点文件描述符等于lfd,并且是读事件,那么就是lfd变化,需要提取连接
				if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN)
				{
					int cfd = Accept(lfd, NULL, NULL); // 提取新的连接,返回提取的新的已连接套接字
					if( cfd > 0 )
					{
						ev.data.fd = cfd;
						ev.events = EPOLLIN;
						// 设置cfd非阻塞
						int flag = fcntl(cfd, F_GETFL);
						flag |= O_NONBLOCK;
						fcntl(cfd, F_SETFL, flag);
						epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev); // 将新得已连接套接字节点上树
					}
				}
				else if(evs[i].events & EPOLLIN) // 否则如果是读事件变化,代表是普通的cfd变化
				{
					read_info(&evs[i], epfd); // 读取客户端请求,处理请求信息
				}
			}
		}
	}

	// 扫尾












	return 0;
}

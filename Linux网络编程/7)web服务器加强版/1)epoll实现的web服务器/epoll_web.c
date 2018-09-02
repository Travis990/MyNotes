/* ************************************************************************
 *       Filename:  epoll_web.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年09月02日 09时11分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <sys/epoll.h>
 #include <fcntl.h>
#include "wrap.h"
#include <sys/stat.h>
 #include "pub.h"
 #include <dirent.h>
 #include <signal.h>

 #define  PORT 8000
 #define EVENT_MAX 1024
 void send_header(int cfd,int code ,char *info,char *filetype,int length)
 {
 	char buf[1024]="";
 	int len = 0;
 	len = sprintf(buf,"HTTP/1.1 %d %s\r\n",code,info);//组织状态行
 	send(cfd,buf,len,0);//发送状态行
 	//组织消息头
 	len = sprintf(buf,"Content-Type:%s\r\n",filetype);//组织文件类型 必填
	send(cfd,buf,len,0);//发送文件类型行
	if(length > 0)
	{
		len = sprintf(buf,"Content-Length:%d\r\n",length);//组织文件大小
		send(cfd,buf,len,0);//发送文件大小
	}
	send(cfd,"\r\n",2,0);//发送空行
	
 }
 void send_file(int cfd,char *filepath)
 {
 	int fd=0;
 	fd = open(filepath,O_RDONLY);//打开文件
 	if(fd < 0)
 		perror("");
 	int n=0;
 	char buf[1024]="";
 	while(  (n = read(fd,buf,sizeof(buf))) > 0 )//读取文件
 	{
 		int ret = send(cfd,buf,n,0);//发送文件内容
 		printf("ret=%d\n", ret);

 	}
 	close(fd);

 }
 void read_info(struct epoll_event *ev,int epfd)
 {
 		char buf[1024]=""; 
 		char num[1024]=""; 
 		int n =  Readline(ev->data.fd, buf, sizeof(buf));//读取请求行
 		if(n <= 0 )
 		{
 				printf("client close\n");
 				epoll_ctl(epfd,EPOLL_CTL_DEL,ev->data.fd,ev);
 				close(ev->data.fd);

 		}
 		printf("[%s]\n",buf );
 		while(  (n = Readline(ev->data.fd, num, sizeof(num))) > 0 );//将请求内容读干净
 		//GET  /  http/1.1 \r\n
 		//GET /%E8%8B%A6%E7%93%9C.txt HTTP/1.1
 		char method[128],content[128],protocol[128];
 		sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,content,protocol);
 		printf(" [%s] [%s]  [%s]\n",method,content,protocol );
 		//解析请求行数据
 		if( strcasecmp(method,"GET") == 0)//比较请求方法method是否是get请求
 		{
 			//%E8%8B%A6%E7%93%9C.txt
 			printf("strcasecmp\n");
 	 		char *strfile = content+1;
 	 		strdecode(strfile, strfile);
 	 		if(*strfile  == 0)
 	 			strfile  = "./"	;
			//得到请求的文件   stat()
			struct stat s;
			if( stat(strfile,&s)< 0 )//文件不存在
			{
				printf("这个文件没有找到\n");
					//发送一个error.html
				//发送消息头
				// void send_header(int cfd,int code ,char *info,char *filetype,int length)	
				send_header(ev->data.fd,404,"NOT FOUND",get_mime_type("*.html"),0);
				//发送文件
				send_file(ev->data.fd,"error.html");

			}
 			else if(  S_ISREG(s.st_mode)) ////如果在发送这个文件  先发送消息头,在发送文件
 			{
 					printf("这是一个普通的文件\n");//.jpg
 					send_header(ev->data.fd,200,"OK",get_mime_type(strfile),s.st_size);
 					send_file(ev->data.fd,strfile);
 			}
 			else if(S_ISDIR(s.st_mode))
 			{
 					printf("这是一个目录\n");
 					send_header(ev->data.fd,200,"OK",get_mime_type("*.html"),0);
 					//发送一个根目录的html文件,分3部分发送
 					//1 发送header.html
 					send_file(ev->data.fd,"dir_header.html");
 					//2 发送列表
 					//读取目录
 					struct dirent **list=NULL;
 					char send_buf[1024]="";
 					int send_len=0;
 					int file_num = scandir(strfile,&list,NULL,alphasort );
 					for(int i=0;i<file_num;i++)
 					{
 						//printf("%s\n", list[i]->d_name);
 						if( DT_DIR ==list[i]->d_type )
 						{
 						send_len = sprintf(send_buf,"<li><a href='%s/'>%s/</a></li>",list[i]->d_name,list[i]->d_name);
 						
 						}
 						else  
 						{
 							send_len = sprintf(send_buf,"<li><a href='%s'>%s</a></li>",list[i]->d_name,list[i]->d_name);

 						}
 						send(ev->data.fd,send_buf,send_len,0);
 						free(list[i]);

 					}
 					free(list);
 					//3 发送tail.html
 					send_file(ev->data.fd,"dir_tail.html");

 			}
 			
 			
 		}

 }
 int main(int argc, char const *argv[])
 {
 	signal(SIGPIPE, SIG_IGN);//忽略SIGPIPE信号
 	char mydir[128]="";
 	strcpy(mydir,getenv("PWD"));///home/itheima/share/c++10_net/day07webserver
 	sprintf(mydir,"%s/web-http",mydir);
 	printf("mydir= [%s]\n",mydir );
 	chdir(mydir);
 	//chdir("/home/itheima/share/c++10_net/day07webserver/web-http");//切换工作路径
 	//创建套接字
 	//绑定
 	int lfd = tcp4bind(PORT,NULL);
 	//监听
 	Listen(lfd,128);
 	//创建树
 	int epfd = epoll_create(1);
 	//lfd上树
 	struct epoll_event ev,evs[EVENT_MAX];
 	ev.data.fd = lfd;
 	ev.events = EPOLLIN;
 	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);//将lfd节点上树
 	//循环监听
 	int nreadly = 0;
 	while(1)
 	{
 		nreadly = epoll_wait(epfd,evs,EVENT_MAX,-1);//监听事件
 		if(nreadly > 0)
 		{
 			for(int i=0;i<nreadly;i++)//循环遍历已监听到的节点
 			{
 				//如果evs[i]这个节点文件描述符等于lfd,并且是读事件,那么就是lfd变化,需要提取连接
 				if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN)
 				{
 					int cfd = Accept(lfd,NULL,NULL);//提取新的连接,返回提取的新的已连接套接字
 					if(cfd > 0)
 					{
 						ev.data.fd = cfd;
 						ev.events = EPOLLIN;
 						//设置cfd非阻塞
 						int flag = fcntl(cfd,F_GETFL);
 						flag |= O_NONBLOCK;
 						fcntl(cfd,F_SETFL,flag);
 						epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);//将新得已连接套接字节点上树

 					}

 				}
 				else if(evs[i].events & EPOLLIN)//否则如果是读事件变化,代表是普通的cfd变化
 				{

 					//read_info(&evs[i],epfd);//读取客户端请求,处理请求信息
 					read_info(&evs[i],epfd);//读取客户端请求,处理请求信息
 				}

 			}


 		}


 	}
 	//扫尾
 	return 0;
 }




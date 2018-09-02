/* ************************************************************************
 *       Filename:  epoll_webser.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年09月01日 14时46分12秒
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

#include <string.h>

#include <dirent.h>
 #define  PORT 8000
 #define EVENT_MAX 1024
 void send_header1(int fd ,int code ,char *info,char *filetype,int length)
 {
	 printf("$$$$$$$$$00101\n");
 	char buf[1024]="";
 	int len =0;
 	len = sprintf(buf,"HTTP/1.1 %d %s\r\n",code,info);
	printf("fd=%d\n",fd);
 	send(fd,buf,len,0);
 	len = sprintf(buf,"Content-Type:%s\r\n",filetype);
	send(fd,buf,len,0);
	if(length > 0)
	{
		len = sprintf(buf,"Content-Length:%d\r\n",length);
		send(fd,buf,len,0);
    }
	send(fd,"\r\n",2,0);
	 printf("$$$$$$$$$00102\n");
 }
 void send_header(int cfd,int code,char *info,char *filetype,int length)
{
	char buf[1024]="";
	//发送状态行
	int len ;
	len = sprintf(buf,"HTTP/1.1 %d %s\r\n",code,info);
	send(cfd,buf,len,0);
	//发送消息头
	len = sprintf(buf,"Content-Type:%s\r\n",filetype);
	send(cfd,buf,len,0);
	if(length > 0)
	{
		len = sprintf(buf,"Content-Length:%d\r\n",length);
		send(cfd,buf,len,0);

	}
	//空行
	send(cfd,"\r\n",2,0);

}
void send_file(int cfd,char *filepath)
{
	int sfd = open(filepath,O_RDONLY);
	if(sfd < 0)
	{
		perror("");
		return ;
	}
	char buf[1024]="";
	int n=0;
	while( ( n = read(sfd,buf,sizeof(buf))) > 0 ) 
	{
		int ret = send(cfd,buf,n,0);
		printf("###%d###\n", ret);
	}
	close(sfd);

}
 void send_file1(int cfd,char *filepath)
 {
	 
	 printf("$$$$$$$$$001\n");
 	printf("filepath=%s\n", filepath);
 	int fd = open(filepath,O_RDONLY);
 	if(fd < 0)
 		perror("");
	 printf("$$$$$$$$$002\n");
 	char buf[1024]="";
 	int n=0;
 	while( (n= read(fd,buf,sizeof(buf))) > 0  )
 	{
 		printf("n=%d\n",n );
 		int ret = send(cfd,buf,n,0);
 		
 		printf("ret=%d\n",ret);

 	}
 	printf("##########1\n");
 	close(fd);
 }
 void read_info3(struct epoll_event *ev,int epfd)
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
 	//	printf("read ok\n");
 		//解析请求行数据

 		//得到请求的文件   stat()
 		//判断请求的文件在不在web-http目录
 		//如果在发送这个文件  先发送消息头,在发送文件
 		//如果不在发送error.html文件,先发送消息头,在发送error,html文件
 		char method[128],content[128],protocol[128];
 		sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,content,protocol);
 		printf("[%s]  [%s]  [%s]\n", method,content,protocol);
 		char *strfile = content+1;
 		struct stat s;
 		if( stat(strfile,&s) < 0)
 		{
 			//发送头
 			//void send_header(int fd ,int code ,char *info,char *filetype,int length)
 			send_header1(ev->data.fd,404,"NOT FOUND",get_mime_type("*.html"),0);
 			//发送文件
 			send_file1(ev->data.fd,"error.html");

 		}
 		else
 		{
 			printf("#1\n");
 			//printf("%s\n", );
 				send_header1(ev->data.fd,200,"OK",get_mime_type(strfile),s.st_size);
 			//发送文件
 			send_file1(ev->data.fd,strfile);
 			printf("#2\n");

 		}





 }
 void read_info2(int cfd,int epfd)
 {
 		char buf[1024]=""; 
 		char num[1024]=""; 
 		int n =  Readline(cfd, buf, sizeof(buf));//读取请求行
 		if(n <= 0 )
 		{
 			struct epoll_event ev;
 			ev.data.fd = cfd;
 			ev.events = EPOLLIN;
 				printf("client close\n");
 				epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,&ev);
 				close(cfd);

 		}
 		printf("[%s]\n",buf );
 		while(  (n = Readline(cfd, num, sizeof(num))) > 0 );//将请求内容读干净
 	//	printf("read ok\n");
 		//解析请求行数据

 		//得到请求的文件   stat()
 		//判断请求的文件在不在web-http目录
 		//如果在发送这个文件  先发送消息头,在发送文件
 		//如果不在发送error.html文件,先发送消息头,在发送error,html文件
 		char method[128],content[128],protocol[128];
 		sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",method,content,protocol);
 		printf("[%s]  [%s]  [%s]\n", method,content,protocol);
 		char *strfile = content+1;
 		struct stat s;
 		if( stat(strfile,&s) < 0)
 		{
 			//发送头
 			//void send_header(int fd ,int code ,char *info,char *filetype,int length)
 			send_header(cfd,404,"NOT FOUND",get_mime_type("*.html"),0);
 			//发送文件
 			send_file(cfd,"error.html");

 		}
 		else
 		{
 			printf("#1\n");
 			//printf("%s\n", );
 				send_header(cfd,200,"OK",get_mime_type(strfile),s.st_size);
 			//发送文件
 			send_file(cfd,strfile);
 			printf("#2\n");

 		}





 }
 void read_info(int cfd,int epfd)
{
	char buf[EVENT_MAX]="";
	char num[EVENT_MAX]="";
	int n = Readline(cfd,buf,sizeof(buf));
	if(n <= 0)
	{
		printf("close\n");
		struct epoll_event ev;
		ev.data.fd = cfd;
		ev.events = EPOLLIN;
		epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,&ev);//将ev节点上树
		close(cfd);

	}
	
	printf("#####%s\n", buf);
	
	while(  (n = Readline(cfd,num,sizeof(num))) > 0 );

	//解析数据
	//GET /hello HTTP/1.1\r\n
	char mothod[128],content[128],protocol[128];
	sscanf(buf,"%[^ ] %[^ ] %[^ \r\n]",mothod,content,protocol);
	printf("[%s] [%s] [%s]\n", mothod,content,protocol);
	if(strcasecmp(mothod,"GET") == 0)
	{
		//GET /%E8%8B%A6%E7%93%9C.txt  HTTP/1.1
		char *strfile = content+1;
		//strdecode(strfile,strfile);
		//if(*strfile == 0)
		//	strfile = "./";//如果没有请求文件,给它一个当前目录
		struct stat s;
		if(stat(strfile,&s) < 0)//如果返回值小于0 ,代表文件 不存在
		{
				//发送消息头
				//在发送error.html
			//void send_header(int cfd,int code,char *info,char *filetype,int length)
			send_header(cfd,404,"NOT FOUND",get_mime_type("*.html"),0);
			//send_file(int cfd,char *filepath)
			send_file(cfd,"error.html");

		}
		else// if(S_ISREG(s.st_mode))//文件存在,请求的是一个普通文件
		{
				send_header(cfd,200,"OK",get_mime_type(strfile),s.st_size);
				send_file(cfd,strfile);

		}
		/*else if(S_ISDIR(s.st_mode))//文件存在,请求的是一个目录
		{
			//发送消息头
			send_header(cfd,200,"OK",get_mime_type("*.html"),0);
			//发送dir_header.html文件
			send_file(cfd,"dir_header.html");
			//发送目录<li></li>
			struct dirent **list;
			int count = scandir(strfile,&list,NULL,alphasort);//读取 目录
			for(int i=0;i<count;i++)
			{
				char buf[1024]="";
				//  <li>%s</li>
				int nready;
				if(list[i]->d_type == DT_DIR)
				{

				 nready = sprintf(buf, "<li><a  href='%s/'>%s</a></li>",list[i]->d_name,list[i]->d_name);
					
				}
				else
				{
					 nready = sprintf(buf, "<li><a  href='%s'>%s</a></li>",list[i]->d_name,list[i]->d_name);
				}
				send(cfd,buf,nready,0);
				free(list[i]);

			}
			free(list);
			//发送dir_tail.html文件
			send_file(cfd,"dir_tail.html");


		}*/


	}



}
 int main(int argc, char const *argv[])
 {
 	char mydir[128]="";
 	strcpy(mydir,getenv("PWD"));
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
 					read_info3(&evs[i],epfd);//读取客户端请求,处理请求信息
 				}

 			}


 		}


 	}
 	//扫尾
 	return 0;
 }

 int main01(int argc, char const *argv[])
{
	//signal(SIGPIPE,SIG_IGN);//屏蔽SIGPIPE信号
	chdir("/home/itheima/share/c++10_net/day07webserver/web-http");//切换工作路径
	//创建套接字
	//绑定
	int lfd = tcp4bind(PORT,NULL);
	//监听
	listen(lfd,128);
	//创建树
	int epfd = epoll_create(1);
	//初始化节点
	struct epoll_event ev,evs[EVENT_MAX];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	//上树
	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);//将ev节点上树
	//循环监听
	int ret=0;
	while(1)
	{
		ret = epoll_wait(epfd,evs,EVENT_MAX,-1);
		if(ret > 0)
		{
			for(int i=0;i<ret;i++)//遍历evs数组
			{
				if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN)//如果是lfd变化,并且是EPOLLIN事件,是新的连接到来
				{
					int cfd = Accept(lfd,NULL,NULL);//提取新的连接
					//将已连接套接字上树监听
					ev.data.fd = cfd;
					ev.events = EPOLLIN;
					//设置文件描述符为非阻塞
					int flag = fcntl(cfd,F_GETFL);
					flag |= O_NONBLOCK;
					fcntl(cfd,F_SETFL,flag);
					//上树
					epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);//将ev节点上树

				}
				else if(evs[i].events & EPOLLIN) //如果是普通的读事件,客户端发来信息
				{
					read_info(evs[i].data.fd,epfd);

				}

			}


		}


	}
	//扫尾

	return 0;
}


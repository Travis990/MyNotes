#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>                         
#include <unistd.h>  
#include <fcntl.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

int main()
{
	 // 创建通信端点：套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if(sockfd < 0)  
    {  
        perror("socket");  
        return -1;  
    }  
      
    // 设置本地地址结构体  
    struct sockaddr_in my_addr;  
    bzero(&my_addr, sizeof(my_addr));   // 清空      
    my_addr.sin_family = AF_INET;   	// ipv4  
    my_addr.sin_port   = htons(8000);   // 端口  
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip  
      
    // 绑定  
    int err_log = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr));  
    if( err_log != 0)  
    {  
        perror("binding");  
        close(sockfd);        
        return -1;  
    }  
      
    err_log = listen(sockfd, 10); // 监听，监听套接字改为被动  
    if(err_log != 0)  
    {  
        perror("listen");  
        close(sockfd);        
        return -1;    
    }     
      
    printf("listen client @port=%d...\n", 8000); 
	
	int connfd;  
    connfd = accept(sockfd, NULL, NULL);    // 等待连接  
	
	char recv_buf[8*1024] = {0};
    read(connfd, recv_buf, sizeof(recv_buf));
    printf("%s", recv_buf);
	
	//获取客户端需要的网页内容
	char filename[200] = {0};
	sscanf(recv_buf, "GET /%[^ ]", filename); //获取文件名字
	printf("filename = %s\n", filename);
	
	int fd;
	fd = open(filename, O_RDONLY);//只读方式打开
	if(fd < 0)//打开文件失败
	{
		//HTTP 响应报文由状态行、响应头部、空行、响应包体4个部分组成
		char err[]=	"HTTP/1.1 404 Not Found\r\n"	//状态行
					"Content-Type: text/html\r\n"	//响应头部
					"\r\n"							//空行
					"<HTML><BODY>File not found</BODY></HTML>";  //响应包体           
					
		perror("open");	
		send(connfd, err, strlen(err), 0);//发送失败的响应报文头
		
		close(connfd);
		return -1;
	}	
	
	//HTTP 响应报文由状态行、响应头部、空行、响应包体4个部分组成
	char head[] = "HTTP/1.1 200 OK\r\n" 	//状态行
			  "Content-Type: text/html\r\n"	//响应头部
			  "\r\n";						//空行
	send(connfd, head, strlen(head), 0); //发送成功的响应报文头
	
	//发送响应包体
	int len;
	char file_buf[4 * 1024];
	//循环读取并发送文件，读多少，发多少
	while((len = read(fd, file_buf, sizeof(file_buf))) > 0) 
	{
		send(connfd, file_buf, len, 0);
	}
	
	close(fd);
	close(connfd); 

    while(1)
    {
        NULL;
    }
	
	return 0;
}
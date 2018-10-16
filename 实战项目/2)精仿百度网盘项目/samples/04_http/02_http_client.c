#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>                         
#include <unistd.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

int main()
{
	 // 创建通信端点：套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  
   
    // 设置服务器地址结构体  
    struct sockaddr_in server_addr;  
    bzero(&server_addr,sizeof(server_addr)); // 初始化服务器地址  
    server_addr.sin_family = AF_INET;   // IPv4  
    server_addr.sin_port = htons(80); // nginx服务器监听的端口 
    inet_pton(AF_INET, "192.168.31.109", &server_addr.sin_addr);   // 服务器ip  
      
     // 主动连接服务器  
    int err_log = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));  
	if(err_log != 0)  
    {  
        perror("connect");  
        close(sockfd);  
        return -1;  
    }
	
	//http请求报文包
	char send_buf[] = 
		"GET /index.html HTTP/1.1\r\n"
		"Accept: image/gif, image/jpeg, image/pjpeg, application/x-ms-application, application/xaml+xml, application/x-ms-xbap, */*\r\n"
		"Accept-Language: zh-Hans-CN,zh-Hans;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
		"User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727; .NET CLR 3.0.30729; .NET CLR 3.5.30729)\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Host: 192.168.31.109:8000\r\n"
		"Connection: Keep-Alive\r\n"
		"\r\n";
	
	//发送http请求报文包
	send(sockfd, send_buf, sizeof(send_buf)-1, 0);

	//获取http响应报文
	char recv_buf[8*1024] = {0};
    recv(sockfd, recv_buf, sizeof(recv_buf), 0);
    printf("%s", recv_buf);
	
	return 0;
}

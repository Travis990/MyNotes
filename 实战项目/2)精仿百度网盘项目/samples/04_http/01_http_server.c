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
	
	char buf[8*1024] = {0};
    read(connfd, buf, sizeof(buf));
    printf("%s", buf);
	

    while(1)
    {
        NULL;
    }
	
	return 0;
}
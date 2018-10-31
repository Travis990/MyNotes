//socket udp 客户端
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 10088
int main()
{
    //创建socket对象
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);

    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    char buf[] = "Hello Server";
    sendto(sockfd,&buf,
            sizeof(buf),0,(struct sockaddr*)&addr,sizeof(addr));
    socklen_t len=sizeof(addr);
    close(sockfd);
}

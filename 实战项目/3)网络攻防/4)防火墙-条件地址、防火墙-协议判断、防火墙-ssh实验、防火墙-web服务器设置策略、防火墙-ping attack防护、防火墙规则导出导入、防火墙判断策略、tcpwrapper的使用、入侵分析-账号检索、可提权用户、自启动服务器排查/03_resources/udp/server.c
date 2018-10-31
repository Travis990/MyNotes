//socket udp 服务端
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERVER_ADDR "0.0.0.0"
#define SERVER_PORT 10088

int main()
{
    //创建socket对象
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);

    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_port =htons(SERVER_PORT);
    addr.sin_addr.s_addr=inet_addr(SERVER_ADDR);

    //绑定socket对象与通信链接
    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
        printf("bind\n");
        return -1;

    }

    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);

    printf("Server is running ...\n");
    while(1)
    {
        char buf[1024]={0};
        int recv = recvfrom(sockfd,&buf,sizeof(buf)-1,0,(struct sockaddr*)&cli,&len);
        printf("recv size = %d: %s \n",recv,buf);
    }
    close(sockfd);
}

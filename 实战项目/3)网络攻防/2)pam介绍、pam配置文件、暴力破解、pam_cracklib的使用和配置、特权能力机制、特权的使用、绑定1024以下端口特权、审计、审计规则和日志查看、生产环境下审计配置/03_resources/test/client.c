#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SER_ADDR "192.168.0.119"
#define SER_PORT 9999
//#define SER_ADDR "172.16.28.98"

/* main function */
int main(int argc, char *argv[])
{
    /**
     * Step 1: 创建一个socket， 指定SOCK_STREAM参数代表基于TCP协议
     *   如果是UDP协议，则需要用SOCK_DGRAM
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);       


    /**
     * Step 2: 设置目标主机IP地址和端口号
     *   IP+Port， 标识网络上某个主机的通信进程
     */
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(struct sockaddr_in));        
    dest.sin_family = AF_INET;                        
    dest.sin_addr.s_addr = inet_addr(SER_ADDR);
    dest.sin_port = htons(SER_PORT);                     

    /**
     * Step 3: 连接服务器
     *
     */
    if (connect(sockfd, (struct sockaddr *)&dest,       
                sizeof(struct sockaddr_in)) != 0){
        /* 此处SYN Flood攻击会用到 */
        fprintf(stdout, "Error for connect: %s\n", strerror(errno));
        return 1;
    }

    /**
     * Step 4: 向Server发送数据
     */

    char *buffer1 = "Hello Server!\n";
    char *buffer2 = "Hello Again!\n";
    write(sockfd, buffer1, strlen(buffer1));       

    write(sockfd, buffer2, strlen(buffer2));

    /**
     *  Step 5: 关闭连接
     */
    close(sockfd);                               

    return 0;
}


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SER_ADDR 9999

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;
    struct sockaddr_in my_addr, client_addr;
    char buffer[100];

    /**
     * Step 1: 创建一个socket， 指定SOCK_STREAM代表TCP
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /**
     *  Step 2:   绑定一个端口号
     */
    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SER_ADDR);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) <0){
        perror("Error for bind");
        return 1;
    }

    /**
     * Step 3: 监听连接
     */
    listen(sockfd, 5);

    fprintf(stdout, "Serve listenning....\n");
    while(1){
        /**
         * Step 4: Accept 一个连接请求
         */
        socklen_t client_len = sizeof(client_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

        /**
         * Step 5: 从当前连接读取数据 */
        memset(buffer, 0, sizeof(buffer));
        int len = read(newsockfd, buffer, 100);
        printf("Received %d bytes: %s", len, buffer);

        /**
         * Step 6: 关闭当前链接*/
        close(newsockfd);
    }

    /**
     * Step 7: 关闭套接字
     */
    close(sockfd);

    return 0;
}

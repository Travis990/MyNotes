#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "poolsocket.h"

//线程处理函数
void *myroute(void *arg)
{
    unsigned char *out = NULL;
    int outLen = 0;
    int ret = -1;
    int connfd = -1;
    int timeout = 3;

    connfd = (int)(long)arg;

    while(1)
    {
        //3. 接收客户端数据
        ret = sckServer_rev(connfd, timeout, &out, &outLen); //1
        if (0 != ret)
        {
            printf("sckServer_rev failed...\n"); 
            break;
        }

        printf("recv from client: %s outLen: %d\n", out, outLen);

        //4. 发送响应数据
        ret = sckServer_send(connfd, timeout, out, outLen);
        if (0 != ret)
        {
            printf("sckServer_send failed....\n"); 
            break;
        }

        //5. 释放内存
        sck_FreeMem((void **)&out);
    }

    //6. 关闭连接
    sckServer_close(connfd);  

    return NULL;
}

int main(void)
{
    int ret = -1;
    int port = 10086;
    int sockfd = -1;
    int timeout = 3;
    int connfd = -1;

    pthread_t tid = -1;

    //1. 服务器端初始化
    ret = sckServer_init(port, &sockfd);
    if (0 != ret)
    {
        printf("sckServer_init failed...\n"); 
        return 1;
    }
    printf("服务器初始化Ok....\n");

    while(1)
    {
        //2. 接受连接
        ret = sckServer_accept(sockfd, timeout, &connfd);
        if (0 != ret)
        {
            printf("sckServer_accept failed...\n"); 
            continue;
        }

        //创建一个线程
        pthread_create(&tid, NULL, myroute, (void*)(long)connfd);

        //分离线程
        pthread_detach(tid); 
    }

    //3. 关闭连接
    sckServer_close(sockfd);

    //4. 销毁客户端
    sckServer_destroy();

    return 0;
}

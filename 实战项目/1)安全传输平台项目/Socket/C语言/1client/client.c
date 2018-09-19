#include "poolsocket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int ret = -1;

    char *ip = "192.168.11.51";
    int port = 10086;
    int timeout = 3;
    int connfd = -1;

    unsigned char *data = "hello itcast";

    //传出参数
    unsigned char *out = NULL;
    int outLen = 0;

    //1.  客户端 初始化 
    ret = sckClient_init();
    if (0 != ret)
    {
        printf("sckClient_init failed....\n");
        return 1;
    }

    //2. 客户端 连接服务器 
    ret = sckClient_connect(ip, port, timeout, &connfd);
    if (0 != ret)
    {
        printf("sckClient_connect failed....\n"); 

        sckClient_destroy();
        return 1;
    }
    printf("客户端连接服务端ok....\n");

    //3. 客户端 发送报文 
    ret = sckClient_send(connfd, timeout, data, strlen(data));
    if (0 != ret)
    {
        printf("sckClient_send failed....\n"); 

        sckClient_destroy();
        return 1;
    }

    //4.  客户端 接受报文 
    ret = sckClient_rev(connfd, timeout, &out, &outLen); //1
    if (0 != ret)
    {
        printf("sckClient_rev failed....\n"); 

        sckClient_destroy();
        return 1;
    }
    printf("out: %s outLen: %d\n", out, outLen);

    //5. 释放内存 
    sck_FreeMem((void **)&out);

    //6. 客户端 关闭和服务端的连接 
    sckClient_closeconn(connfd);

    //7. 客户端 释放 
    sckClient_destroy();

    return 0;
}

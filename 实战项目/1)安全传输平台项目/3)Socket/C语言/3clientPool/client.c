#include "poolsocket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int ret = -1;
    int connfd = -1;

    void *handle = NULL;

    unsigned char *data = "hello itcast";

    unsigned char *out = NULL;
    int outLen = 0;

    SCKClitPoolParam param = {
        .serverip = "192.168.11.51",
        .serverport = 10086,
        .bounds = 5,
        .connecttime = 3,
        .sendtime = 3,
        .revtime = 3
    };

    /* 客户端 socket池初始化 */
    ret = sckCltPool_init(&handle, &param);
    if (0 != ret)
    {
        printf("sckCltPool_init failed....\n"); 
        return 1;
    }
    printf("客户端连接池初始化ok....\n");

    /* 客户端 socket池 获取一条连接 */
    ret = sckCltPool_getConnet(handle, &connfd);
    if (0 != ret)
    {
        printf("sckCltPool_getConnet failed....\n"); 
        return 1;
    }

    /* 客户端 socket池 发送数据 */ 
    ret = sckCltPool_send(handle, connfd, data, strlen(data));
    if (0 != ret)
    {
        printf("sckCltPool_send failed...\n"); 
        return 1;
    }

    /* 客户端 socket池 接受数据 */
    ret = sckCltPool_rev(handle, connfd, &out, &outLen); //1
    if (0 != ret)
    {
        printf("sckCltPool_rev failed....\n"); 
        return 1;
    }
    printf("recv:  out:%s  outLen: %d\n", out, outLen);

    /* 客户端 socket池 把连接放回 socket池中 */ 
    sckCltPool_putConnet(handle, connfd, 0); //0正常 1

    /* 客户端 socket池 销毁连接 */
    sckCltPool_destroy(handle);

    return 0;
}

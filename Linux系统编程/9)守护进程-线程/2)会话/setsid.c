#include <stdio.h>
#include <stdlib.h> 

#include <sys/types.h>
#include <unistd.h>

/*
#include <unistd.h>

pid_t setsid(void);
功能：
	创建一个会话，并以自己的ID设置进程组ID，同时也是新会话的ID。调用了setsid函数的进程，既是新的会长，也是新的组长。
参数：无
返回值：
	成功：返回调用进程的会话ID
	失败：-1
*/

//创建一个会话   会话是一个进程组或者多个进程组的集合
int main(void)
{
    pid_t pid = -1;

    pid = setsid();
    if (-1 == pid)
    {
        perror("setsid"); 
        goto err0;
    }

    while(1)
    {
        printf("hello world\n"); 
        sleep(1);
    }
    
    return 0;
err0:
    return 1;
}

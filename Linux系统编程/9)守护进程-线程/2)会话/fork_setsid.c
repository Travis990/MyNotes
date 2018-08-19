#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

#include <sys/types.h>
#include <unistd.h>

/*
#include <unistd.h>

pid_t getsid(pid_t pid);
功能：获取进程所属的会话ID
参数：
	pid：进程号，pid为0表示查看当前进程session ID
返回值：
	成功：返回调用进程的会话ID
	失败：-1
*/
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

#if 0
    //创建一个子进程
    pid = fork();
    if (-1 == pid)
    {
        perror("fork"); 
        goto err0;
    }

    if (pid > 0)
    {
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
    }
#endif
    printf("sid:%d\n", getsid(0));
    
    return 0;
err0:
    return 1;
}

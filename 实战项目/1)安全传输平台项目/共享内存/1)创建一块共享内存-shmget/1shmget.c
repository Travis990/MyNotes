#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
    int shmid = -1;

    //如果与0x55关联的共享内存段不存在, 那么就会创建一个, 如果存在, 就直接返回一个句柄
    //shmid = shmget(0x55, 1024, IPC_CREAT | 0644);
    //如果与0x55关联的共享内存段不存在就创建, 如果存在, 就报错
    shmid = shmget(0x55, 1024, IPC_CREAT | IPC_EXCL | 0644);
    //打开已经存在共享内存, 返回句柄
    //shmid = shmget(0x55, 0, 0);
    //创建一个私有的共享内存段  私有意思就是其它进程不能与该共享内存关联
    //shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0644);
    if (-1 == shmid)
    {
        perror("shmge");
        printf("shmget failed....ret: %d\n", shmid); 
        return 1;
    }

    printf("shmid:%d\n", shmid);

    return 0;
}

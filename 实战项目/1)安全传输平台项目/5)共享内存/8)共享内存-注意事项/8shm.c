#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 如果有多个进程共有一块共享内存, 当其中一个进程把"共享内存"删除了, 其他已经关联此块共享内存的进程依然可以继续使用!
// 但是被删除的"共享内存"不会第一时间的去释放, 而是做了下标志. 等最后一个关联它的进程使用完解除关联以后才会释放.
// 被标志为"已删除的共享内存" 不允许被未进行过关联的进程使用!

int main(void)
{
    int shmid = -1;
    int ret = -1;

    void *addr = NULL;

    //1. 获取shmid
    shmid = shmget(0x55, 1024, IPC_CREAT |  0644);
    if (-1 == shmid)
    {
        perror("shmge");
        printf("shmget failed....ret: %d\n", shmid); 
        return 1;
    }

    printf("shmid:%d\n", shmid);


    //2. 关联共享内存
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //NULL表示由系统选择一个合适的没有使用的地址进行关联
    //0 表示共享内存段可以读写
    addr = shmat(shmid, NULL, 0);
    if ((void *)-1 == addr)
    {
        perror("shmat"); 
        return 1;
    }
    printf("关联共享内存成功 addr: %p\n", addr);
    printf("按下任意键解除共享内存关联\n");
    getchar();

    //3. 解除关联
    ret = shmdt(addr);
    if (-1 == ret)
    {
        perror("shmdt"); 
        return 1;
    }

    printf("共享内存解除关联ok....\n");

    printf("按下任意键删除共享内存....\n");
    getchar();

    //4. 删除共享内存
    ret = shmctl(shmid, IPC_RMID, NULL);
    if (-1 == ret)
    {
        perror("shmctl"); 
        return 1;
    }

    return 0;
}

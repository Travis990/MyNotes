#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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

    printf("按下任意键程序退出....\n");
    getchar();

    return 0;
}

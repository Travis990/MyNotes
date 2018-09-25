#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define SIZE 1024

//读共享内存
int main(void)
{
    int ret = -1;
    int shmid = -1;
    void *addr = NULL;

    char buf[SIZE];
    
    //1. 创建共享内存或者获取共享内存shmid
    shmid = shmget(0x55, SIZE, IPC_CREAT | 0644); 
    if (-1 == shmid)
    {
        perror("shmget"); 
        return 1;
    }

    //2. 与共享内存关联
    void *shmat(int shmid, const void *shmaddr, int shmflg);
    addr = shmat(shmid, NULL, 0);
    if ((void *)-1 == addr)
    {
        perror("shmat");  
        return 1;
    }
    //memset(addr, 0, SIZE);

    //3. 读共享内存
    memset(buf, 0, SIZE);
    memcpy(buf, addr, SIZE);

    printf("buf: %s\n", buf);

    //4. 解除关联
    ret = shmdt(addr);
    if (-1 == ret)
    {
        perror("shmdt"); 
        return 1;
    }


    return 0;
}

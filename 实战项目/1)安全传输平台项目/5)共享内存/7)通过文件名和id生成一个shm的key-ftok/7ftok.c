#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
    int shmid = -1;

    key_t key = -1;

    //通过文件名字和id生成一个key
    //key_t ftok(const char *pathname, int proj_id);
    //key = ftok("./a.out", 'A');
    //第一个参数可以是目录
    //key = ftok("/home", 'A');
    //第一个参数也可以是文件绝对路径
    key = ftok("/tmp/deng.vim", 'A');
    if (-1 == key)
    {
        perror("ftok"); 
        return 1;
    }

    printf("key: %d\n", key);

#if 0
    shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0644);
    if (-1 == shmid)
    {
        perror("shmge");
        printf("shmget failed....ret: %d\n", shmid); 
        return 1;
    }

    printf("shmid:%d\n", shmid);
#endif

    return 0;
}

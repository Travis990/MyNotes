//基于event的服务器编写
#include <event.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define _MAX_CLIENT_  1024  

typedef struct FdEventMap{
    int fd;//文件描述符
    struct event *ev;//对应事件
}FdEvent;

FdEvent mFdEvents[_MAX_CLIENT_];

//struct event* readev = NULL;

void initEventArray()
{
    int i;
    for(i = 0 ; i < _MAX_CLIENT_ ; i ++){
        mFdEvents[i].fd = -1;
        mFdEvents[i].ev = NULL;
    }
}
int addEvent(int fd,struct event *ev)
{
    int i;
    for(i = 0; i < _MAX_CLIENT_; i ++){
        if(mFdEvents[i].fd < 0){
            break;
        }
    }
    if(i == _MAX_CLIENT_){
        printf("too many clients ...\n");
        return -1;
    }
    mFdEvents[i].fd = fd;
    mFdEvents[i].ev = ev;
    return 0;
}
void destroyEventArray()
{
    int i;
    for(i = 0 ; i < _MAX_CLIENT_ ; i ++){
        if(mFdEvents[i].fd > 0 && mFdEvents[i].ev){
            close(mFdEvents[i].fd);
            mFdEvents[i].fd = -1;
            event_free(mFdEvents[i].ev);
        }
    }
}
struct event* getEventByFd(int fd)
{
    int i;
    for(i = 0; i < _MAX_CLIENT_ ; i ++){
        if(mFdEvents[i].fd == fd){
            //匹配
            return mFdEvents[i].ev;
        }
    }
    return NULL;
}

//void (*event_callback_fn)(evutil_socket_t, short, void *);
void readcb(evutil_socket_t fd, short events, void *arg)
{
    char buf[256];
    int ret = recv(fd,buf,sizeof(buf),0);
    if(ret <= 0){
        close(fd);
        event_del(getEventByFd(fd));
    }else{
        int i;
        for(i = 0 ; i < ret ; i ++){
            buf[i] = toupper(buf[i]);
        }
        send(fd,buf,ret,0);
    }
}
void conncb(evutil_socket_t fd, short events, void *arg)
{
    struct event_base*base = (struct event_base*)arg;//得到base
    struct sockaddr_in client;
    socklen_t lth = sizeof(client);
    int cfd = accept(fd,(struct sockaddr*)&client,&lth);
    if(cfd > 0){
        //应该继续监听
        struct event * readev = event_new(base,cfd,EV_READ|EV_PERSIST,readcb,base);
        event_add(readev,NULL);
        //添加到数组
        addEvent(cfd,readev);
    }
}

int main()
{
    //根节点
    struct event_base *base = event_base_new();
    //创建套接字
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    //绑定
    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = 0x00;
    serv.sin_port = htons(8888);
    int opt =1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(bind(lfd,(struct sockaddr*)&serv,sizeof(serv)) < 0){
        perror("bind err");
        return -1;
    }
    //监听
    listen(lfd,128);
    //创建事件-设置回调
    initEventArray();//初始化事件数组
    //struct event *event_new(struct event_base *, evutil_socket_t, short, event_callback_fn, void *);
    struct event *connev = event_new(base,lfd,EV_READ|EV_PERSIST,conncb,base);
    //监听事件 -- event_add
    event_add(connev,NULL);

    //循环等待
    event_base_dispatch(base);
    //释放根节点
    event_free(connev);//释放事件
    //event_free(readev);
    destroyEventArray();
    event_base_free(base);
    return 0;
}


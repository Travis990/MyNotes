//bufferevent建立客户端的过程
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>

int tcp_connect_server(const char* server_ip, int port);
void cmd_msg_cb(int fd, short events, void* arg);
void server_msg_cb(struct bufferevent* bev, void* arg);
void event_cb(struct bufferevent *bev, short event, void *arg);

int main(int argc, char** argv)
{
    if( argc < 3 )
    {
        //两个参数依次是服务器端的IP地址、端口号
        printf("please input 2 parameter\n");
        return -1;
    }
    //创建根节点
    struct event_base *base = event_base_new();
    //创建并且初始化buffer缓冲区
    struct bufferevent* bev = bufferevent_socket_new(base, -1,
                                                     BEV_OPT_CLOSE_ON_FREE);

    //监听终端输入事件 设置标准输入的监控,设置回调是 cmd_msg_cb 
    struct event* ev_cmd = event_new(base, STDIN_FILENO,
                                     EV_READ | EV_PERSIST,
                                     cmd_msg_cb, (void*)bev);
    //上树 开始监听标准输入的读事件
    event_add(ev_cmd, NULL);
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr) );
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    //将ip地址转换为网络字节序
    inet_aton(argv[1], &server_addr.sin_addr);

    //连接到 服务器ip地址和端口 初始化了 socket文件描述符 socket+connect 
    bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr,
                               sizeof(server_addr));
    //设置buffer的回调函数 主要设置了读回调 server_msg_cb ,传入参数是标准输入的读事件
    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, (void*)ev_cmd);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    event_base_dispatch(base);//循环等待
    event_free(ev_cmd);
    bufferevent_free(bev);
    event_base_free(base);
    printf("finished \n");
    return 0;
}
//终端输入回调
void cmd_msg_cb(int fd, short events, void* arg)
{
    char msg[1024];

    int ret = read(fd, msg, sizeof(msg));
    if( ret < 0 )
    {
        perror("read fail ");
        exit(1);
    }
    //得到bufferevent指针,目的是为了写到bufferevent的写缓冲区
    struct bufferevent* bev = (struct bufferevent*)arg;

    //把终端的消息发送给服务器端
    bufferevent_write(bev, msg, ret);
}

void server_msg_cb(struct bufferevent* bev, void* arg)
{
    char msg[1024];

    size_t len = bufferevent_read(bev, msg, sizeof(msg));
    msg[len] = '\0';

    printf("recv %s from server\n", msg);
}

void event_cb(struct bufferevent *bev, short event, void *arg)
{

    if (event & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (event & BEV_EVENT_ERROR)
        printf("some other error\n");
    else if( event & BEV_EVENT_CONNECTED)
    {
        printf("the client has connected to server\n");
        return ;
    }

    //这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
    //释放event事件 监控读终端
    struct event *ev = (struct event*)arg;
    event_free(ev);
}



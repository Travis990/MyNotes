/*
  This exmple program provides a trivial server program that listens for TCP
  connections on port 9995.  When they arrive, it writes a short message to
  each client connection, and closes each connection once it is flushed.

  Where possible, it exits cleanly in response to a SIGINT (ctrl-c).
*/


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 9995;

static void listener_cb(
	struct evconnlistener *, // 连接侦听器的地址
	evutil_socket_t,
	struct sockaddr *, 
	int socklen, 
	void *
);

static void conn_writecb(
	struct bufferevent *, 
	void *
);

static void conn_eventcb(
	struct bufferevent *, 
	short, void *
);

static void signal_cb(
	evutil_socket_t, 
	short, 
	void *
);

int
main(int argc, char **argv)
{
	struct event_base *base; // 根节点定义
	struct evconnlistener *listener; //监听器定义
	struct event *signal_event; // 信号事件

	struct sockaddr_in sin; // 套接字地址信息
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new(); // 创建根节点
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}
	
	//给绑定的结构体地址初始化,ip地址为初始化,填0 ,代表绑定通配地址
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	//创建链接侦听器(socket,bind,listen,accept),会创建监听套接字,如果监听套接字监听到有新的连接变化,提取链接,回调listener函数
	// 1.struct evconnlistener *evconnlistener_new_bind(struct event_base *base,
	//		evconnlistener_cb cb, void *ptr, unsigned flags, int backlog,
	//		const struct sockaddr *sa, int socklen
	//	);
	/*
		Flags 需要参考几个值：
		LEV_OPT_LEAVE_SOCKETS_BLOCKING   文件描述符为阻塞的
		LEV_OPT_CLOSE_ON_FREE            关闭时自动释放
		LEV_OPT_REUSEABLE                端口复用
		LEV_OPT_THREADSAFE               分配锁，线程安全
	*/
	listener = evconnlistener_new_bind(
		base, // base根节点
		listener_cb, // 创建链接侦听器回调函数
		(void *)base, // base根节点
		LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, // 端口复用, 关闭时自动释放
		-1, // 如果backlog是-1，那么监听器会自动选择一个合适的值，如果填0，那么监听器会认为listen函数已经被调用过了(即在外面已定义了listen)
		(struct sockaddr*)&sin, // 保存返回客户端的地址信息
		sizeof(sin) // sin结构体大小
	);
	
	// 连接成功判断
	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}
	
	// 初始化了一个event节点.当SIGINT信号产生, 回调signal_cb
	signal_event = evsignal_new(
		base, // base根节点
		SIGINT, // 监听按下 Ctrl + C 退出信号触发signal_cb函数
		signal_cb, // 如果用户按下 Ctrl + C 触发该回调函数
		(void *)base
	);
	
	// 将signal_event节点上树监听, event_add上树 -开始监听信号事件
	if (!signal_event || event_add(signal_event, NULL)<0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base); // 循环监听  阻塞

	evconnlistener_free(listener); // 释放连接侦听器
	event_free(signal_event); // 释放signal_event节点
	event_base_free(base); // 释放base根节点

	printf("done\n");
	return 0;
}

// 链接监听器帮助处理了 accept连接，得到新的文件描述符，作为参数传入
static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = user_data;
	struct bufferevent *bev; //定义bufferevent事件
	
	// 创建新的bufferevent事件，对应的与客户端通信的socket
	/*
		1. struct bufferevent *bufferevent_socket_new(struct event_base *base, evutil_socket_t fd, int options);
		bufferevent_socket_new 对已经存在socket创建bufferevent事件，可用于后面讲到的链接监听器的回调函数中，参数说明：
		base – 对应根节点
		fd   -- 文件描述符
		options – bufferevent的选项
			BEV_OPT_CLOSE_ON_FREE   -- 释放bufferevent自动关闭底层接口    
			BEV_OPT_THREADSAFE      -- 使bufferevent能够在多线程下是安全的
	*/
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	
	// 设置回调函数 只设置了写回调和事件产生回调
	bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
	// 启用读写缓冲区
	bufferevent_enable(bev, EV_WRITE);
	// 禁用读缓冲
	bufferevent_disable(bev, EV_READ);
	// 将MESSAGE 写到输出缓冲区
	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

static void
conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);//查看bufferevent缓冲区的数据
	if (evbuffer_get_length(output) == 0) {//如果数据长度为0,说明数据已经写到底层的缓冲区
		printf("flushed answer\n");
		bufferevent_free(bev);//释放节点,下树,并且关闭cfd
	}
}

static void
conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	} else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
		    strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	 * timeouts */
	bufferevent_free(bev);
}

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = user_data;
	struct timeval delay = { 2, 0 }; // 设置延迟时间 2s

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay); // 延时2s退出
}

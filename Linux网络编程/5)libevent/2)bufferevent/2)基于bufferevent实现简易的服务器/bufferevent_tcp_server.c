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

static void listener_cb(struct evconnlistener *, evutil_socket_t,
    struct sockaddr *, int socklen, void *);
static void conn_writecb(struct bufferevent *, void *);
static void conn_eventcb(struct bufferevent *, short, void *);
static void signal_cb(evutil_socket_t, short, void *);
static void rcb(struct bufferevent *bev, void *user_data);

int
main(int argc, char **argv)
{
	struct event_base *base;//用来存base根节点的地址
	struct evconnlistener *listener;//存连接侦听器的地址
	struct event *signal_event;//存一个普通的event事件的节点地址

	struct sockaddr_in sin;
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();//创建一个base根节点
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}
//给绑定的结构体地址初始化,ip地址为初始化,填0 ,代表绑定通配地址
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	//创建链接侦听器(socket,bind,listen,accept),会创建监听套接字,如果监听套接字监听到有新的连接变化,提取链接,回调listener函数
	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	    (struct sockaddr*)&sin,
	    sizeof(sin));

	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}
	//初始化了一个event节点.当SIGINT信号产生,回调signal_cb

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0) {//将signal_event节点上树监听
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base);//循环监听  阻塞

	evconnlistener_free(listener);//释放连接侦听器
	event_free(signal_event);//释放signal_event节点
	event_base_free(base);//释放base根节点

	printf("done\n");
	return 0;
}

static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);//创建 一个bufferevent节点
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, rcb, conn_writecb, conn_eventcb, NULL);//设置回调
	bufferevent_enable(bev, EV_WRITE | EV_READ);//让读写事件使能
//	bufferevent_disable(bev, EV_READ);//让读回调非使能

//	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

static void rcb(struct bufferevent *bev, void *user_data)
{
	char buf[1024]="";
	int n =  bufferevent_read(bev,buf,sizeof(buf));//从bufferevent缓冲区中读取数据
	printf("%s\n",buf);
	bufferevent_write(bev,buf,n);//从bufferevent缓冲区中读取数据


}
static void
conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);//查看bufferevent缓冲区的数据
	if (evbuffer_get_length(output) == 0) {//如果数据长度为0,说明数据已经写到底层的缓冲区
		printf("flushed answer\n");
	//	bufferevent_free(bev);//释放节点,下树,并且关闭cfd
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
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);//2s 之后退出循环监听
}

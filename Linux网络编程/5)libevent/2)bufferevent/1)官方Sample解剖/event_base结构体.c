//event_base 定义在event-internal.h文件中
struct event_base {
	const struct eventop *evsel;      //表示选择的事件引擎，可能为:epoll, poll, select
	void *evbase;                     //全局对象
	/* evsel和evbase这两个字段的设置可能会让人有些迷惑，这里你可以把evsel和evbase看作是类和静态函数的关系，
	比如添加事件时的调用行为：evsel->add(evbase, ev)，实际执行操作的是evbase；这相当于class::add(instance, ev)，instance就是class的一个对象实例。
	evsel指向了全局变量static const struct eventop *eventops[]中的一个；
	前面也说过，libevent将系统提供的I/O demultiplex机制统一封装成了eventop结构；因此eventops[]包含了select、poll、kequeue和epoll等等其中的若干个全局实例对象。
	evbase实际上是一个eventop实例对象；先来看看eventop结构体，它的成员是一系列的函数指针, 在event-internal.h文件中：
	struct eventop {
	const char *name;
	void *(*init)(struct event_base *); // 初始化
	int (*add)(void *, struct event *); // 注册事件
	int (*del)(void *, struct event *); // 删除事件
	int (*dispatch)(struct event_base *, void *, struct timeval *); // 事件分发
	void (*dealloc)(struct event_base *, void *); // 注销，释放资源 
	int need_reinit;// set if we need to reinitialize the event base 
	};
	也就是说，在libevent中，每种I/O demultiplex机制的实现都必须提供这五个函数接口，来完成自身的初始化、销毁释放；对事件的注册、注销和分发。
	比如对于epoll，libevent实现了5个对应的接口函数，并在初始化时并将eventop的5个函数指针指向这5个函数，那么程序就可以使用epoll作为I/O demultiplex机制了 */
 
	int event_count;   /* counts number of total events */
	int event_count_active; /* counts number of active events */
	int event_gotterm;  /* Set to terminate loop */
	int event_break;  /* Set to terminate loop immediately */
 
	/* active event management */
	struct event_list **activequeues;
	int nactivequeues;
	/*是一个二级指针，前面讲过libevent支持事件优先级，因此你可以把它看作是数组，
	其中的元素activequeues[priority]是一个链表， 链表的每个节点指向一个优先级为priority的就绪事件event。*/
 
	struct evsignal_info sig; /* signal handling info,是来管理信号的结构体 */
	struct event_list eventqueue;//链表，保存了所有的注册事件event的指针。
	struct min_heap timeheap;  //用来检测事件是否超时的堆栈,是管理定时事件的小根堆
	struct timeval event_tv;        //系统的当前时间
	struct timeval tv_cache;   //与event::ev_timeout进行比较,确定事件是否超时
	//event_tv和tv_cache是libevent用于时间管理的变量
};

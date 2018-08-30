//在event2/event_struct.h中event的结构描述
struct event {
	TAILQ_ENTRY (event) ev_next;            /*增加下一个事件*/
	TAILQ_ENTRY (event) ev_active_next;     /*增加下一个活动事件*/
	TAILQ_ENTRY (event) ev_signal_next;     /*增加下一个信号*/
	/*ev_next，ev_active_next和ev_signal_next都是双向链表节点指针；它们是libevent对不同事件类型和在不同的时期，对事件的管理时使用到的字段。
	libevent使用双向链表保存所有注册的I/O和Signal事件，ev_next就是该I/O事件在链表中的位置；称此链表为“已注册事件链表”；
	同样ev_signal_next就是signal事件在signal事件链表中的位置；
	ev_active_next：libevent将所有的激活事件放入到链表active list中，然后遍历active list执行调度，ev_active_next就指明了event在active list中的位置；*/
 
	unsigned int min_heap_idx;         /* for managing timeouts 表示该event保存在min_heap数组中的索引*/ 
	struct timeval ev_timeout;   //用来保存事件的超时时间
	/*min_heap_idx和ev_timeout，如果是timeout事件，它们是event在小根堆中的索引和超时值，libevent使用小根堆来管理定时事件*/
 
	struct event_base *ev_base;   /* 该事件所属的反应堆实例，这是一个event_base结构体*/
 
	int ev_fd;               /*对于I/O事件，是绑定的文件描述符；对于signal事件，是绑定的信号*/
	short ev_events;        /*event关注的事件类型，它可以是以下3种类型：
							I/O事件： EV_WRITE和EV_READ
							定时事件：EV_TIMEOUT
							信号：    EV_SIGNAL
							辅助选项：EV_PERSIST，表明是一个永久事件
							Libevent中的定义为：
							#define EV_TIMEOUT 0x01   
							#define EV_READ  0x02   
							#define EV_WRITE 0x04   
							#define EV_SIGNAL 0x08   
							#define EV_PERSIST 0x10 
							可以看出事件类型可以使用“|”运算符进行组合，需要说明的是，信号和I/O事件不能同时设置；
							还可以看出libevent使用event结构体将这3种事件的处理统一起来；*/ 
	void *ev_arg; /*回调函数的参数,void*，表明可以是任意类型的数据，在设置event时指定*/
	void (*ev_callback)(int fd, short events, void *arg);   
	/*event的回调函数，被ev_base调用，执行事件处理程序，这是一个函数指针，
	其中参数fd对应于ev_fd；events对应于ev_events；arg对应于ev_arg*/
 
	int ev_pri;  /* smaller numbers are higher priority */
 
	short ev_ncalls;        /*事件就绪执行时，调用ev_callback的次数，通常为1*/ 
	short *ev_pncalls; /* Allows deletes in callback ,指针，通常指向ev_ncalls或者为NULL*/
	int ev_res;  /* result passed to event callback ,记录了当前激活事件的类型*/
	int ev_flags; /*libevent用于标记event信息的字段，表明其当前的状态，可能的值有：
				  #define EVLIST_TIMEOUT 0x01 // event在time堆中   
				  #define EVLIST_INSERTED 0x02 // event在已注册事件链表中   
				  #define EVLIST_SIGNAL 0x04 // 未见使用   
				  #define EVLIST_ACTIVE 0x08 // event在激活链表中   
				  #define EVLIST_INTERNAL 0x10 // 内部使用标记   
				  #define EVLIST_INIT     0x80 // event已被初始化  
				  #define EVLIST_TIMEOUT 0x01 // event在time堆中
				  #define EVLIST_INSERTED 0x02 // event在已注册事件链表中
				  #define EVLIST_SIGNAL 0x04 // 未见使用
				  #define EVLIST_ACTIVE 0x08 // event在激活链表中
				  #define EVLIST_INTERNAL 0x10 // 内部使用标记
				  #define EVLIST_INIT     0x80 // event已被初始化 */          
};

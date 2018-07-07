#include "linkQueue.h"

// 初始化
void* init_link_queue()
{
	return init();
}

// 入队
void push_link_queue(void *queue, void *data)
{
	insert(queue, 0, data);
}

// 出队
void pop_link_queue(void *queue)
{
	remove_by_pos(queue, get_size(queue) - 1);
}

// 获取队头元素
void* get_link_queue_head(void *queue)
{
	return get_node(queue, get_size(queue) - 1);
}

// 获取队尾元素
void* get_link_queue_tail(void *queue)
{
	return get_node(queue, 0);
}

// 获取元素个数
int get_link_queue_size(void *queue)
{
	return get_size(queue);
}

// 销毁队列
void destroy_link_queue(void *queue)
{
	destroy(queue);
}
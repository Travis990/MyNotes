#include "SeqQueue.h"

// 初始化
void* init()
{
	SeqQueue *queue = (SeqQueue*)malloc(sizeof(SeqQueue));
	if (NULL == queue)
	{
		return NULL;
	}
	queue->size = 0;
	for (int i = 0; i < 1024; i++)
	{
		queue->data[i] = NULL;
	}

	return queue;
}

// 入队
void push(void *_queue, void *_data)
{
	if (NULL == _queue || NULL == _data)
	{
		return;
	}

	SeqQueue *queue = (SeqQueue*)_queue;
	if (queue->size == 1024) // 队列满了
	{
		return;
	}
	for (int i = queue->size - 1; i >= 0; i--)
	{
		queue->data[i + 1] = queue->data[i];
	}

	queue->data[0] = _data;
	queue->size++;
}

// 出队
void pop(void *_queue)
{
	if (NULL == _queue)
	{
		return;
	}
	SeqQueue *queue = (SeqQueue*)_queue;
	if (queue->size == 0)
	{
		return;
	}

	queue->size--;
}

// 获取队头元素
void* get_queue_head(void *_queue)
{
	if (NULL == _queue)
	{
		return NULL;
	}
	SeqQueue *queue = (SeqQueue*)_queue;
	return queue->data[queue->size - 1];
}

// 获取队尾元素
void* get_queue_tail(void *_queue)
{
	if (NULL == _queue)
	{
		return NULL;
	}
	SeqQueue *queue = (SeqQueue*)_queue;
	return queue->data[0];
}

// 获取元素个数
int get_size(void *_queue)
{
	if (NULL == _queue)
	{
		return -1;
	}
	SeqQueue *queue = (SeqQueue*)_queue;
	return queue->size;
}

// 销毁队列
void destroy(void *_queue)
{
	if (NULL != _queue)
	{
		free(_queue);
		_queue = NULL;
	}
}
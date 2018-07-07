#include "LinkStack.h"

// 初始化
void* init()
{
	LinkStack *stack = (LinkStack*)malloc(sizeof(LinkStack));
	if (NULL == stack)
	{
		return NULL;
	}
	stack->head.next = NULL;
	stack->size = 0;

	return stack;
}

// 入栈
void push(void *_stack, void *_data)
{
	if (NULL == _stack || NULL == _data)
	{
		return;
	}
	LinkStack *stack = (LinkStack*)_stack;
	Node *node = (Node*)_data;

	// 入栈
	node->next = stack->head.next;
	stack->head.next = _data;

	stack->size++;
}

// 出栈
void pop(void *_stack)
{
	if (NULL == _stack)
	{
		return;
	}
	LinkStack *stack = (LinkStack*)_stack;
	if (stack->size == 0)
	{
		return;
	}
	Node *pDel = stack->head.next;
	stack->head.next = pDel->next;

	stack->size--;
}

// 获取栈的顶元素
void* get_stack_top(void *_stack)
{
	if (NULL == _stack)
	{
		return NULL;
	}
	LinkStack *stack = (LinkStack*)_stack;
	return stack->head.next;
}

// 获取元素个数
int get_size(void *_stack)
{
	if (NULL == _stack)
	{
		return -1;
	}
	LinkStack *stack = (LinkStack*)_stack;
	return stack->size;
}

// 销毁栈
void destroy(void *_stack)
{
	if (NULL != _stack)
	{
		free(_stack);
		_stack = NULL;
	}
}

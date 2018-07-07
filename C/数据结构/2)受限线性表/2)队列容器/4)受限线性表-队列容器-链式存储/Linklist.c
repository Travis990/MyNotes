#include "Linklist.h"

// 初始化函数
void* init()
{
	// 头节点的空间
	Linklist *list = (Linklist*)malloc(sizeof(Linklist));
	if (NULL == list)
	{
		return NULL;
	}
	list->head.next = NULL;
	list->size = 0;
	return list;
}

// 指定位置插入
void insert(void *_list, int _pos, void *_data)
{
	if (NULL == _list || NULL == _data)
	{
		return;
	}
	Linklist *list = (Linklist*)_list;
	Node *data = (Node*)_data;
	if (_pos < 0 || _pos > list->size)
	{
		_pos = list->size;
	}

	// 找到pos位置节点的前一个节点
	Node *pCur = &(list->head);
	for (int i = 0; i < _pos; i++)
	{
		pCur = pCur->next;
	}

	// 将新节点入链表
	data->next = pCur->next;
	pCur->next = data;

	// 更新节点数
	list->size++;
}

// 遍历
void each(void *_list, void(*_each)(void*))
{
	if (NULL == _list || NULL == _each)
	{
		return;
	}
	Linklist *list = (Linklist*)_list;
	Node *pCur = list->head.next;
	while (NULL != pCur)
	{
		_each(pCur);
		pCur = pCur->next;
	}
}

// 根据位置获取值
void* get_node(void *_list, int _pos)
{
	if (NULL == _list)
	{
		return NULL;
	}
	Linklist *list = (Linklist*)_list;
	if (_pos < 0 || _pos > list->size - 1)
	{
		return NULL;
	}

	Node *pCur = &(list->head);
	for (int i = 0; i < _pos; i++)
	{
		pCur = pCur->next;
	}
	return pCur->next;
}

// 获取元素个数
int get_size(void *_list)
{
	if (NULL == _list)
	{
		return -1;
	}
	Linklist *list = (Linklist*)_list;
	return list->size;
}

// 根据位置删除
void remove_by_pos(void *_list, int _pos)
{
	if (NULL == _list)
	{
		return;
	}
	Linklist *list = (Linklist*)_list;
	if (list->size == 0)
	{
		return;
	}
	if (_pos<0 || _pos>list->size - 1)
	{
		return;
	}

	Node *pCur = &(list->head);
	for (int i = 0; i < _pos; i++)
	{
		pCur = pCur->next;
	}

	// 缓存待删除的节点
	Node *Del = pCur->next;
	// 重新建立前后驱关系
	pCur->next = Del->next;

	list->size--;
}

// 销毁
void destroy(void *_list)
{
	if (NULL != _list)
	{
		free(_list);
		_list = NULL;
	}
}
#include "Linklist.h"

// 初始化函数
List init()
{
	// 头节点空间
	Linklist *list = (Linklist*)malloc(sizeof(Linklist));
	if (NULL == list)
	{
		return NULL;
	}
	list->size = 0;
	list->head.data = NULL;
	list->head.next = NULL;

	return list;
}

// 指定位置插入 pos=1 那么在有效节点的第0个和第1个之间插入
int insert(List _list, int _pos, void *_data)
{
	if (NULL == _list || NULL == _data)
	{
		return -1;
	}

	Linklist *list = (Linklist*)_list;

	if (0 > _pos || _pos > list->size)
	{
		_pos = list->size;
	}

	// 定义辅助指针
	Node *pCur = &(list->head); // 因为head是实体
	for (int i = 0; i < _pos; i++)
	{
		pCur = pCur->next;
	}

	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = _data;
	newnode->next = NULL;

	// 新节点入链表
	newnode->next = pCur->next;
	pCur->next = newnode;

	// 更新当前节点数量
	list->size++;

	return 0;
}

// 头插
int push_front(List _list, void *_data)
{
	return insert(_list, 0, _data);
}

// 尾插
int push_back(List _list, void *_data)
{
	Linklist *list = (Linklist*)_list;
	return insert(_list, list->size, _data);
}

// 指定值前面插入数据  老值和节点的值进行比较  通过用户传入的函数进行比较值
int insert_by_val(List _list, void *_oldval, void *_newval, int(*_compare)(void*, void*))
{
	if (NULL == _list || NULL == _oldval || NULL == _newval || NULL == _compare)
	{
		return -1;
	}

	Linklist *list = (Linklist*)_list;

	// 定义两个辅助指针
	Node *pPre = &(list->head); // 前一个节点元素
	Node *pCur = pPre->next; // 当前元素

	while (NULL != pCur)
	{
		if (_compare(pCur->data, _oldval))
		{
			// 创建新节点
			Node *newnode = (Node*)malloc(sizeof(Node));
			newnode->data = _newval;
			newnode->next = NULL;

			// 新节点入链表
			pPre->next = newnode;
			newnode->next = pCur;

			list->size++;
			break;
		}

		pPre = pCur;
		pCur = pCur->next;
	}

	return 0;
}

// 指定位置删除
int remove_by_pos(List _list, int _pos)
{
	if (NULL == _list)
	{
		return -1;
	}
	Linklist *list = (Linklist*)_list;
	if (list->size == 0)
	{
		return -1;
	}
	if (_pos<0 || _pos>list->size - 1)
	{
		return -2;
	}

	// 寻址位置
	Node *pCur = &(list->head);

	for (int i = 0; i < _pos; i++)
	{
		pCur = pCur->next;
	}

	// 这时, pCur是要删除的节点的上一个节点
	Node *pDel = pCur->next;
	// 重新建立前后驱关系
	pCur->next = pDel->next; // 断开了pDel这个节点
	// 释放节点空间
	free(pDel);
	pDel = NULL;

	list->size--;

	return 0;
}

// 指定值删除
int remove_by_val(List _list, void *_data, int(*_compare)(void*, void*))
{
	if (NULL == _list || NULL == _data || NULL == _compare)
	{
		return -1;
	}
	Linklist *list = (Linklist*)_list;

	Node *pPre = &(list->head);
	Node *pCur = pPre->next;

	while (NULL != pCur)
	{
		if (_compare(pCur->data, _data))
		{
			pPre->next = pCur->next;
			free(pCur);
			list->size--;
			break;
		}
		pPre = pCur;
		pCur = pCur->next;
	}
	return 0;
}

// 头删
int pop_front(List _list)
{
	return remove_by_pos(_list, 0);
}

// 尾删
int pop_back(List _list)
{
	Linklist *list = (Linklist*)_list;
	return remove_by_pos(_list, list->size - 1);
}

// 遍历
void each(List _list, void(*_each)(void*))
{
	if (NULL == _list || NULL == _each)
	{
		return;
	}
	Linklist *list = (Linklist*)_list;
	// 定义辅助指针
	Node *pCur = list->head.next; // 从有效节点开始遍历
	while (NULL != pCur)
	{
		_each(pCur->data);
		pCur = pCur->next;
	}
}

// 销毁
void destroy(List _list)
{
	if (NULL == _list)
	{
		return;
	}
	Linklist *list = (Linklist*)_list;
	// 从有效节点开始删除
	Node *pCur = list->head.next; // 第一个有效节点
	while (NULL != pCur)
	{
		// 存储下一个节点的地址
		Node *tmp = pCur->next;
		// 释放当前节点
		free(pCur);
		pCur = tmp;
	}
	// 释放头节点
	free(list);
	list = NULL;
}
#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 链表的节点
typedef struct Node {
	void *data;
	struct Node *next;
}Node;

// 链表
typedef struct Linklist {
	Node head; // 链表的头节点
	int size; // 节点个数
}Linklist;

typedef void * List; // 伪装链表类型,其实是 void*

// 初始化函数
List init();

// 指定位置插入 pos=1 那么在有效节点的第0个和第1个之间插入
int insert(List, int, void*);

// 头插
int push_front(List, void*);

// 尾插
int push_back(List, void*);

// 指定值前面插入数据  老值和节点的值进行比较  通过用户传入的函数进行比较值
int insert_by_val(List, void*, void*, int(*)(void*, void*));

// 指定位置删除
int remove_by_pos(List, int);

// 指定值删除
int remove_by_val(List, void*, int(*)(void*, void*));

// 头删
int pop_front(List);

// 尾删
int pop_back(List);

// 遍历
void each(List, void(*)(void*));

// 销毁
void destroy(List);
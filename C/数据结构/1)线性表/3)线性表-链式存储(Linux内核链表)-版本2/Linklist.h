#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 让用户的数据包含这个结构体
typedef struct Node {
	struct Node *next;
}Node;

typedef struct Linklist {
	Node head;
	int size;
}Linklist;

// 初始化函数
void* init();

// 指定位置插入
void insert(void*, int, Node*);

// 遍历
void each(void*, void(*)(void*));

// 根据位置获取值
void* get_node(void*, int);

// 获取元素个数
int get_size(void*);

// 根据位置删除
void remove_by_pos(void*, int);

// 销毁
void destroy(void*);
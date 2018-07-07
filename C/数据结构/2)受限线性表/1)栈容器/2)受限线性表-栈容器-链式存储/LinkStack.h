#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node *next;
}Node;

typedef struct LinkStack {
	Node head;
	int size;
}LinkStack;

// 初始化
void* init();

// 入栈
void push(void*, void*);

// 出栈
void pop(void*);

// 获取栈的顶元素
void* get_stack_top(void*);

// 获取元素个数
int get_size(void*);

// 销毁栈
void destroy(void*);
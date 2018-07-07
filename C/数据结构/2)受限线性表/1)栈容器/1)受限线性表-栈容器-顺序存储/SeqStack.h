#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 顺序栈
typedef struct SeqStack {
	void *data[1024];
	int size;
}SeqStack;

// 初始化栈
void* init();

// 入栈
void push(void*, void*);

// 出栈
void pop(void*);

// 获取元素个数
int get_size(void*);

// 获取栈顶元素
void* get_stack_top(void*);

// 销毁栈
void destroy(void*);

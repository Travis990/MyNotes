#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 顺序存储
typedef struct SeqQueue {
	void *data[1024]; // 指针数组
	int size;
}SeqQueue;

// 初始化
void* init();

// 入队
void push(void*, void*);

// 出队
void pop(void*);

// 获取队头元素
void* get_queue_head(void*);

// 获取队尾元素
void* get_queue_tail(void*);

// 获取元素个数
int get_size(void*);

// 销毁队列
void destroy(void*);
#pragma once
#include "Linklist.h" // 引入之前封装好的 Linux内核链表-链式存储版本2

// 初始化
void* init_link_queue();

// 入队
void push_link_queue(void*, void*);

// 出队
void pop_link_queue(void*);

// 获取队头元素
void* get_link_queue_head(void*);

// 获取队尾元素
void* get_link_queue_tail(void*);

// 获取元素个数
int get_link_queue_size(void*);

// 销毁队列
void destroy_link_queue(void*);
#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DynamicArray {
	void **data; // 数据空间的首地址
	int capacity; // 容量
	int size; // 元素个数
}DA;

// 定义函数类型
typedef int(compare)(void*, void*);

// 初始化动态数组函数
void* init_array();

// 指定位置插入数据
int insert(void*, int, void*);

// 头部插入
int push_front(void*, void*);

// 尾部插入
int push_back(void*, void*);

// 指定位置删除
int remove_by_pos(void*, int);

// 根据值来删除,第三个参数是需要用户传入函数地址
int remove_by_val(void*, void*, compare*);

// 头部删除
int pop_front(void*);

// 尾部删除
int pop_back(void*);

// 获取数组的大小
int get_size(void*);

// 获取容量
int get_capacity(void*);

// 打印数据的函数
void each(void*, void(*)(void*));

// 销毁数组
int destroy_array(void*);
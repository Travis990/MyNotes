#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
using namespace std;

class Myarr
{
public:
	Myarr();
	// 让用户指定数组的大小和初始值
	Myarr(int Capacity, int val);
	// 有成员指针，打算在构造函数中申请堆区空间，在析构函数中释放堆区空间
	// 写自己的拷贝构造函数
	Myarr(const Myarr &m);
	// 赋值函数（重载赋值运算符）
	Myarr& operator=(const Myarr &arr);
	~Myarr();

	// 重载数组下标[]
	int& operator[](int index);

	// 尾插
	void PushBack(int val);

	// 头插
	void PushFront(int val);

	// 尾删
	void PopBack();

	// 头删
	void PopFront();

	// 获取元素个数
	int getSize();

	// 获取容量
	int getCapacity();

	// 指定位置插入元素
	void InserArr(int pos, int val);

	// 获取指定位置的值
	int& getPosByVal(int pos); // 让函数能当左值和右值

	// 指定位置修改值
	void setPosByVal(int pos, int val);
public:
	int *p; // 存储数组的首地址
	int mSize; // 元素个数
	int mCapacity; // 容量
};


#include "Myarr.h"

Myarr::Myarr()
{
	this->mCapacity = 20;
	this->mSize = 0;
	this->p = new int[this->mCapacity];
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->p[i] = 0;
	}
}


Myarr::~Myarr()
{
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
}

// 让用户指定数组的大小和初始值
Myarr::Myarr(int Capacity, int val = 0)
{
	this->mCapacity = Capacity;
	this->mSize = Capacity;

	this->p = new int[this->mCapacity];
	for (int i = 0; i < this->mCapacity; i++)
	{
		this->p[i] = val;
	}
}

// 有成员指针，打算在构造函数中申请堆区空间，在析构函数中释放堆区空间
// 写自己的拷贝构造函数
Myarr::Myarr(const Myarr &m)
{
	this->mCapacity = m.mCapacity;
	this->mSize = m.mSize;
	this->p = new int[this->mCapacity];
	// 拷贝数据
	for (int i = 0; i < this->mSize; i++)
	{
		this->p[i] = m.p[i];
	}
}

// 尾插
void Myarr::PushBack(int val)
{
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	this->p[this->mSize] = val;
	this->mSize++;
}
// 头插
void Myarr::PushFront(int val)
{
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	for (int i = this->mSize - 1; i >= 0; i--)
	{
		this->p[i + 1] = this->p[i];
	}

	this->p[0] = val;
	this->mSize++;
}

// 尾删
void Myarr::PopBack()
{
	if (this->mSize == 0)
	{
		return;
	}
	this->mSize--;
}
// 头删
void Myarr::PopFront()
{
	if (this->mSize == 0)
	{
		return;
	}
	for (int i = 0; i < this->mSize - 1; i++)
	{
		this->p[i] = this->p[i + 1];
	}
	this->mSize--;
}
// 获取元素个数
int Myarr::getSize()
{
	return this->mSize;
}
// 获取容量
int Myarr::getCapacity()
{
	return this->mCapacity;
}

// 指定位置插入元素
void Myarr::InserArr(int pos, int val)
{
	if (this->mCapacity == this->mSize)
	{
		return;
	}
	// 如果位置不对，让位置变为最后
	if (pos<0 || pos>this->mSize - 1)
	{
		pos = this->mSize;
	}
	for (int i = this->mSize - 1; i >= pos; i--)
	{
		this->p[i + 1] = this->p[i];
	}
	this->p[pos] = val;
	this->mSize++;
}
// 获取指定位置的值
int& Myarr::getPosByVal(int pos) // 让函数能当左值和右值
{
	return this->p[pos];
}
// 指定位置修改值
void Myarr::setPosByVal(int pos, int val)
{
	this->p[pos] = val;
}

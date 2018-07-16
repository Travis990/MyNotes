#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Dejan
{
public:
	Dejan() {}
	Dejan(const char *name)
	{
		cout << "Dejan有参构造" << endl;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void printDejan()
	{
		cout << "printDejan()" << endl;
	}
	~Dejan()
	{
		cout << "Dejan析构函数" << endl;
		if (NULL != this->name)
		{
			delete[] this->name;
			this->name = NULL;
		}
	}
public:
	char *name;
};

class Dejan2
{
public:
	Dejan2() {}
	Dejan2(const char *name)
	{
		cout << "Dejan2有参构造" << endl;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void printDejan2()
	{
		cout << "printDejan2()" << endl;
	}
	~Dejan2()
	{
		cout << "Dejan2析构函数" << endl;
		if (NULL != this->name)
		{
			delete[] this->name;
			this->name = NULL;
		}
	}
public:
	char *name;
};

// 智能管理指针的类
class Student
{
public:
	Student(Dejan *d, Dejan2 *d2)
	{
		cout << "Student有参构造" << endl;
		this->d = d;
		this->d2 = d2;
	}
	Dejan* operator->()
	{
		return this->d;
	}
	Dejan2& operator*()
	{
		return *this->d2; // *this->d2 是对象
	}
	~Student()
	{
		if (NULL != this->d)
		{
			delete this->d; // 释放的是new Dejan；
			this->d = NULL;
		}
		if (NULL != this->d2)
		{
			delete this->d2;
			this->d2 = NULL;
		}
		cout << "Student析构函数" << endl;
	}
public:
	Dejan *d;
	Dejan2 *d2;
};

void test()
{
	Dejan *p = new Dejan;
	Dejan2 *p2 = new Dejan2;

	//s这个对象是在栈区，当test函数结束会去调用Student的析构函数
	//在这个析构函数中释放了从堆区申请的Dejan对象
	Student s(p, p2);
	//s->要返回Dejan类型才能打印出printDejan()
	s->printDejan();

	(*s).printDejan2();
}

int main()
{
	test();

	system("pause");
	return 0;
}
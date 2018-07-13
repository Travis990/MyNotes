#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		cout << "构造函数" << endl;
		a = 10;
		b = 20;
	}

	void init()
	{
		a = 20;
		b = 30;
	}

	void printDejan()
	{
		cout << "a=" << a << " b=" << b << endl;
	}

	Dejan(int a)
	{
		cout << "有参构造" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << a << endl;
		cout << "b=" << b << endl;
	}
public:
	int a;
	int b;
	static int c;
};

int Dejan::c = 1;

// 在C++中使用malloc和free，不会调用构造和析构函数
void test01()
{
	// Dejan dejan; // 栈区

	Dejan *p = (Dejan*)malloc(sizeof(Dejan));
	if (NULL == p)
	{
		cout << "malloc error" << endl;
	}

	cout << p->a << " " << p->b << endl;

	if (NULL != p)
	{
		free(p);
		p = NULL;
	}
}

void test02()
{
	// 从堆区申请了一个对象的空间
	Dejan *p = new Dejan; // 调用无参构造函数

	delete p; // 调用析构函数
	p = new Dejan(10);
	delete p;
}

class Student
{
public:
	Dejan dejan;
};

void test03()
{
	Student s;
	s.dejan.printDejan();
}

void test04()
{
	Dejan a;
	a.a = 10;
	Dejan b;
	b.a = 20;
}

int main()
{
	test04();

	system("pause");
	return 0;
}
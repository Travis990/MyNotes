#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
class A
{

};
class Student
{
	// 构造，析构，拷贝构造，赋值函数（赋值运算符重载）
public:
	Student(int a)
	{
		this->a = a;
	}
public:
	int a;
};

class Dejan
{
	// 构造，析构，拷贝构造，赋值函数（赋值运算符重载）
public:
	Dejan(int a)
	{
		this->a = a;
	}
	// d = d2 ===> m
	Dejan& operator=(Dejan &d2)
	{
		this->a = d2.a;
		return *this;
	}
public:
	int a;
};

void test()
{
	Student s(10);
	Student s2(20);
	cout << "s.a=" << s.a << endl;
	cout << "s2.a=" << s2.a << endl;
	cout << "赋值后:" << endl;

	// 不会报错原因: 编译器提供了一个默认重载赋值运算符的函数
	s = s2;
	cout << "s.a=" << s.a << endl;
	cout << "s2.a=" << s2.a << endl;
	// 赋值函数做了简单的赋值操作
	// s.a = s2.a;
}

void test02()
{
	int a = 10;
	int b = 20;
	int c = 30;

	c = b = a;
}

void test03()
{
	Dejan d(10);
	Dejan d2(20);
	Dejan d3(30);

	// 编译器提供了一个重载赋值运算符的函数
	d3 = d = d2; // 赋值操作

	cout << &d << endl;
	cout << &(d = d2) << endl;
}

int main()
{
	test03();

	system("pause");
	return 0;
}
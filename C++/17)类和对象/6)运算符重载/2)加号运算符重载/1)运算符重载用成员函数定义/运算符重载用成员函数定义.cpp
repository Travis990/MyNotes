#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//运算符重载，就是对已有的运算符重新进行定义
//运算符重载是让代码看起来更加简洁
//运算符重载不能改变运算符本来寓意

class Student
{
public:
	Student(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
public:
	int a;
	int b;
};

class Dejan
{
public:
	//d1+d2  d1是this
	//参数代表加号的右边
	Dejan operator+(Dejan &d2)
	{
		Dejan tmp(this->a + d2.a, this->b + d2.b);
		return tmp;
	}
	//d1+s1;
	//参数代表加号的右边
	Student operator+(Student &s1)
	{
		Student stu(0, 0);
		stu.a = this->a + s1.a;
		stu.b = this->b + s1.b;
		return stu;
	}
	Dejan(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
public:
	int a;
	int b;
};

void test()
{
	Dejan d1(10, 20);
	Dejan d2(30, 50);

	// 当编译器发现这个自定义数据类型定义的变量相加，就会去找operator这个函数
	Dejan d3 = d1 + d2;

	cout << "d3.a=" << d3.a << " d3.b=" << d3.b << endl;
	/*
	d1.a + d2.a;
	d1.b + d2.b;
	*/
}

void test2()
{
	Dejan d1(20, 30);
	Student s1(30, 50);

	Student s2 = d1 + s1;

	//Dejan s2 = d1 + s1;

	cout << "s2.a=" << s2.a << " s2.b=" << s2.b << endl;
}

// 第一个参数代表加号的左边，第二个参数代表加号的右边
/*
Dejan operator+(Dejan &d1,Student &s1)
{
	Dejan d(0,0);
	return d;
}
*/

int main()
{
	test2();

	system("pause");
	return 0;
}
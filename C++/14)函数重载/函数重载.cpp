#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
// 函数重载是为了解决取函数名字的问题
// 函数重载的条件：
// 前提:在同一个作用域
// 1.参数的个数不同
// 2.参数的类型不同
// 3.参数的顺序不同

// 1.参数的个数不同
void add(int a, int b)
{
	cout << "add(int a, int b)" << endl;
}
void add(int a)
{
	cout << "add(int a)" << endl;
}

void test01()
{
	int a = 10;
	int b = 20;
	// add(a,b);
	add('c'); // 编译器做了隐式转换
	// add("liu"); error
}

// 2.参数的类型不同
void add1(double a, double b)
{
	cout << "add1(double a, double b)" << endl;
}
void add1(int a, int b)
{
	cout << "add1(int a, int b)" << endl;
}

void test02()
{
	// 进行严格类型匹配
	add1(10.2, 20.2);
	// add1(10, 20.2); error
}

// 3.参数的顺序不同
void add2(int a,double b)
{
	cout << "add2(int a,double b)" << endl;
}
void add2(double a, int b)
{
	cout << "add2(double a, int b)" << endl;
}
void test03()
{
	add2(10,20.2);
	add2(10.10, 20);
}
void add2(int a)
{
	cout << "add2(int a)" << endl;
}

// 注意：当函数重载和函数的默认参数一起使用时，需要注意二义性问题
void add2(int a, int b = 0)
{
	cout << "add2(int a, int b = 0)" << endl;
}
void test04()
{
	// add2(10); error: 编译器不知道选择
}

int main()
{
	test03();

	system("pause");
	return 0;
}
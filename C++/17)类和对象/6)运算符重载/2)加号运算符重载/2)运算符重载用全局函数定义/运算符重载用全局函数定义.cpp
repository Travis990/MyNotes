#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//运算符重载，就是对已有的运算符重新进行定义
//运算符重载是让代码看起来更加简洁
//运算符重载不能改变运算符本来寓意

class Dejan
{
public:
	Dejan(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
public:
	int a;
	int b;
};
//运算符重载可以写成全局函数，也可以写成成员函数
//运算符重载的函数是编译器去调用

//运算符重载其实就另一种形式的函数调用

//编译器只会去找operator这个函数，不会管函数里面的实现和返回值
Dejan operator+(Dejan &d1, Dejan &d2)
{
	Dejan tmp(d1.a + d2.a, d1.b + d2.b);
	return tmp;
}

void test()
{
	Dejan d1(10, 20);
	Dejan d2(30, 50);

	Dejan d3 = d1 + d2;
	cout << "d3.a=" << d3.a << " d3.b=" << d3.b << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
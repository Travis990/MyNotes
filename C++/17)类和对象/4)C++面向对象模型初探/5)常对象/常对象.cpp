#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 自定义数据类型
class Dejan
{
public:
	Dejan()
	{
		a = 10;
		c = 30;
	}

	void func()const
	{
		cout << "void func()const" << endl;
	}
	void func2()
	{
		cout << "void func2()" << endl;
	}
public:
	int a;
	const int b = 20;

	mutable int c;
};
// 常对象只能调用常函数

void test()
{
	const Dejan dejan; // 常对象
	dejan.func();
	//dejan.func2();  error

	//const int a = 10;
	//常对象可以访问成员变量和const修饰的成员变量，但不能修改
	cout << dejan.a << endl;
	cout << dejan.b << endl;

	//dejan.a = 100; error
	//dejan.b = 200; error
	//常对象对mutable修饰的成员变量可以修改可以访问
	dejan.c = 300;
	cout << dejan.c << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
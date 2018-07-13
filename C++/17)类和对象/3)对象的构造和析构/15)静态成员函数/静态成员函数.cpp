#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//静态成员函数是管理静态成员变量
//静态成员函数使用方式和静态成员变量一样
//静态成员函数不能修改和访问普通成员变量，但是可以访问修改静态成员变量


class Dejan
{
public:
	static int func() // 静态成员函数
	{
		a = 200;

		// b = 20;静态成员函数内是不能修改普通成员变量,也不能访问普通成员变量
		return a;
	}

	void func2()
	{
		cout << a << endl;
	}
private:
	static int a;
	int b;
};
int Dejan::a = 100;

void test()
{
	cout << Dejan::func() << endl;
	Dejan d;
	d.func();
	d.func2();
}

int main()
{
	test();

	system("pause");
	return 0;
}
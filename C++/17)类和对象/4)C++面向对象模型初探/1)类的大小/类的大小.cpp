#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 注意面试会问到: 空类的大小是一个字节
class Dj {};


class Dejan
{
public:
	void func() // 普通成员函数
	{
		a = 20; // 函数里怎么能访问或修改a?
	}
	static void func2() // 静态成员函数
	{

	}
public:
	static int b; // 静态成员变量

	int a; // 普通成员变量
	double c;
};

int Dejan::b = 20;

void test()
{
	cout << sizeof(Dejan) << endl;

	// 类的大小看普通成员变量的大小
	// 成员变量和成员函数是分开存储
}

int main()
{
	test();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	/*Dejan()
	{
		cout << "无参构造函数" << endl;
	}
	Dejan(int a)
	{
		cout << "有参构造函数" << endl;
	}*/
	Dejan(const Dejan &d)
	{
		cout << "拷贝构造函数" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
public:
	int a;
};

void test01()
{
	// Dejan d; // 调用无参构造函数
	// 1.如果用户提供了有参构造函数，那么编译器不会提供无参构造函数
	// 编译器没有提供默认的有参构造函数

	// Dejan d(10);

	// Dejan d2(d); // 调用拷贝构造函数，
	// 2.如果用户自己写了拷贝构造函数，那么编译器不会提供默认的拷贝构造函数
}

void test02()
{
	// Dejan d;  error
	// 3.如果用户自己写了拷贝构造函数，那么编译器不会提供任何构造函数
	// 4.如果用户写了有参构造，那么编译器不会提供无参构造，但是会提供默认的拷贝构造函数
}

int main()
{
	test02();

	system("pause");
	return 0;
}
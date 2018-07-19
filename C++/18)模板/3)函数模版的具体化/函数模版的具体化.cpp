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
		b = 20;
	}
public:
	int a;
	int b;
};

// 不建议具体化
template<class T>
void func(T &a, T &b)
{
	if (a > b)
	{
		cout << "a>b" << endl;
	}
	else
	{
		cout << "a<b" << endl;
	}
}

// 可以把函数模版具体化
template<> void func<Dejan>(Dejan &a, Dejan &b)
{
	cout << "具体化" << endl;
	if (a.a < b.a)
	{
		cout << "a.a<b.a" << endl;
	}
	else
	{
		cout << "a.a>b.a" << endl;
	}
}

void test()
{
	Dejan d1;
	Dejan d2;

	func(d1, d2);
}

int main()
{
	test();

	system("pause");
	return 0;
}
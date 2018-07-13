#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//const修饰的成员函数叫常函数
//常函数不能修改普通成员变量，但可以访问
//mutable修饰的成员变量，常函数可以修改

class Dejan
{
public:
	Dejan(int A, int B)
	{
		a = A;
		b = B;
		c = 10;
	}
	void printDejan()const
	{
		// a = 100; error
		// b = 200; error
		c = 300;
		d = 200;
		cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
	}
public:
	int a;
	int b;
	static int d;
	mutable int c; // 这个常函数可以修改
};
int Dejan::d = 10;

void test()
{
	Dejan d(10, 20);
	d.printDejan();
}

int test02()
{
	static int a = 10;
	a++;
	return a;
}

void test03()
{
	for (int i = 0; i < 10; i++)
	{
		cout << test02() << endl;
	}
}

int main()
{
	test03();

	system("pause");
	return 0;
}
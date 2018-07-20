#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int func1()
{
	throw 1;
}

void test()
{
	try
	{
		func1(); // 函数没有结束，只是中断
		cout << "func1();函数结束" << endl;
	}
	catch (int)
	{
		cout << "捕获一个int类型的异常" << endl;
	}
}

class Dejan
{
public:
	Dejan()
	{
		cout << "构造函数" << endl;
	}
	Dejan(const Dejan &d)
	{
		cout << "拷贝构造" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
};

void func2()
{
	// 当抛出异常时，在函数没有结束的时候，在这个函数中栈中申请的对象都会被释放
	Dejan d;

	throw d; // d会拷贝一份给抛出的对象,假如抛出的对象叫d2
}

void test02()
{
	try
	{
		func2();
	}
	catch (Dejan d3) // Dejan d3 = d2
	{
		cout << "捕获一个Dejan类型的异常" << endl;
		//两个拷贝构造产生的对象在这里被释放 d3 d2
	}
}

char func3()
{
	Dejan d; // 会调用无参构造函数

	throw ('a');

	return 'b';
}

void test03()
{
	try
	{
		func3();
	}
	catch (char a1)
	{
		cout << a1 << endl;
	}
}

int main()
{
	test03();

	system("pause");
	return 0;
}
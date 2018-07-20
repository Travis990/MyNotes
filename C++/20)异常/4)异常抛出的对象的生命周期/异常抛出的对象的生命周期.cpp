#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		cout << "构造函数" << endl;
	}
	Dejan(const Dejan &d)
	{
		cout << "拷贝函数" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
};

void func1()
{
	Dejan d;
	throw d;
}

void test01()
{
	try
	{
		func1();
	}
	catch (Dejan d3) // Dejan d3 = d2;
	{
		cout << "捕获一个Dejan类型的异常" << endl;
		//两个拷贝构造产生的对象在这里被释放 d3 d2
	}
}

void func2()
{
	throw Dejan();
}

void test02()
{
	try
	{
		func2();
	}
	catch (Dejan d)
	{
		cout << "捕获一个Dejan类型的异常" << endl;
	}
}

void func3()
{
	throw Dejan(); // 要catch结束后这行代码才结束
}

void test03()
{
	try
	{
		func3();
	}
	catch (Dejan &d)
	{
		cout << "捕获一个Dejan类型的异常" << endl;
	}
}

void func4()
{
	throw Dejan(); // 要catch结束后这行代码才结束
}

void test04()
{
	try
	{
		func4();
	}
	catch (Dejan *d) // 编译器不允许抛出异常后对栈中的匿名对象取地址操作
	{
		cout << "捕获一个Dejan类型的异常" << endl;
	}
}

void func5()
{
	throw new Dejan; // 要catch结束后这行代码才结束
}

void test05()
{
	try
	{
		func5();
	}
	catch (Dejan *d) // 编译器不允许抛出异常后对栈中的匿名对象取地址操作
	{
		cout << "捕获一个Dejan类型的异常" << endl;
		delete d;
	}
}

// 总结：用抛出匿名对象，在catch中用引用来接
int main()
{
	test05();

	system("pause");
	return 0;
}
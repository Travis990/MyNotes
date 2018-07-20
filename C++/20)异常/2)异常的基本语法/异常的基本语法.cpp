#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	void func()
	{
		cout << "数组越位异常" << endl;
	}
	void fucn2()
	{
		cout << "指针越位异常" << endl;
	}
};

// 1.返回值可以忽略，但异常不能忽略，忽略异常就报错
int myfunc(int a, int b)
{
	if (0 == b)
	{
		// 1.抛出异常
		//throw 1; // 抛出一个int类型的异常
		//throw 'c'; // 抛出一个char类型的异常
		//throw 20.22; // 抛出一个double类型的异常
		//Dejan d;
		//throw d; // 抛出一个Dejan类型的异常
		throw 20.01f;
	}
	return a / b;
}

void test()
{
	int a = 10;
	int b = 0;
	try
	{
		// 2.把可能抛出异常的函数写在try里
		myfunc(a, b);
	}
	catch (int) // 捕获一个int类型的异常
	{
		cout << "捕获一个int类型的异常" << endl;
	}
	catch (char)
	{
		cout << "捕获一个char类型的异常" << endl;
	}
	catch (double)
	{
		cout << "捕获一个double类型的异常" << endl;
	}
	catch (Dejan d)
	{
		cout << "捕获一个Dejan类型的异常" << endl;
		d.func();
		d.fucn2();
	}
	catch (...)
	{
		throw; // 再往上抛出异常
		cout << "捕获其他异常" << endl;
	}
}

int main()
{
	try
	{
		test();
	}
	catch (float)
	{
		cout << "捕获一个float类型的异常" << endl;
	}

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		cout << "无参构造" << endl;
	}
	Dejan(int a)
	{
		cout << "有参构造" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
};
/*
编译阶段
main -->test

test-> new Maker --->调用构造函数Maker()

Maker *q -> delete q; -> 调用析构函数~Maker()

C++不认识void *

*/

void test()
{
	// 不要用void *来接从堆区申请的对象空间
	void *p = new Dejan;

	// 因为delete时不会调用析构函数
	delete p;

	Dejan *q = new Dejan;
	delete q;
}

int main()
{
	test();

	system("pause");
	return 0;
}
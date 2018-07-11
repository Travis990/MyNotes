#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class BMW
{
public:
	BMW(int a)
	{
		age = a;
		cout << "BMW有参构造" << endl;
	}
	~BMW()
	{
		cout << "BMW析构函数" << endl;
	}
public:
	int age;
};

class Buick
{
public:
	Buick(int a)
	{
		cout << "Buick有参构造" << endl;
	}
	Buick(int a, int b)
	{
		cout << "Buick多参构造" << endl;
	}
	~Buick()
	{
		cout << "Buick析构函数" << endl;
	}
};

// 初始化列表是指定调用某种构造函数
// 初始化列表只能写在构造函数里
class Dejan
{
public:
	Dejan(int a, int b) :bmw(a), buick(b, a)
	{
		cout << "Dejan有参构造" << endl;
	}
	~Dejan()
	{
		cout << "Dejan析构函数" << endl;
	}
public:
	Buick buick; // 成员对象
	BMW bmw;
};

void test()
{
	Dejan dejan(30, 60);
	cout << dejan.bmw.age << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
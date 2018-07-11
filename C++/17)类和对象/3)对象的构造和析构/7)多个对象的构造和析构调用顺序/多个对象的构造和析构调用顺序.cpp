#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class BMW
{
public:
	BMW()
	{
		cout << "BMW无参构造" << endl;
	}
	~BMW()
	{
		cout << "BMW析构函数" << endl;
	}
};

class Buick
{
public:
	Buick()
	{
		cout << "Buick无参构造" << endl;
	}
	~Buick()
	{
		cout << "Buick析构函数" << endl;
	}
};

class Dejan
{
public:
	Dejan()
	{
		cout << "Dejan无参构造" << endl;
	}
	~Dejan()
	{
		cout << "Dejan析构函数" << endl;
	}
public:
	Buick buick; // 成员对象
	BMW bmw;
};

// 总结：多个对象的构造和析构函数调用顺序是
// 先调用成员对象的构造函数（成员对象的构造函数调用顺序和定义的顺序一样），再调用本身的构造函数，析构函数的调用顺序反之

//注意：必须保证成员对象的构造和析构能被调用
void test()
{
	Dejan dejan;
}

int main()
{
	test();

	system("pause");
	return 0;
}
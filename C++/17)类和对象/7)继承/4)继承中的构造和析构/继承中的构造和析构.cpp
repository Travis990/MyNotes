#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 注意：有继承，实例化子类对象时，必须保证父类的构造和析构能被调用
class Father
{
public:
	Father(int a)
	{
		cout << "Father 构造函数" << endl;
	}
	~Father()
	{
		cout << "Father 析构函数" << endl;
	}
};

class A
{
public:
	A()
	{
		cout << "A 的构造函数" << endl;
	}
	~A()
	{
		cout << "A 的析构函数" << endl;
	}
};

class B
{
public:
	B()
	{
		cout << "B 的构造函数" << endl;
	}
	~B()
	{
		cout << "B 的析构函数" << endl;
	}
};

class Son :public Father
{
public:
	Son(int a) :Father(a)
	{
		cout << "Son 构造函数" << endl;
	}
	~Son()
	{
		cout << "Son 析构函数" << endl;
	}
public:
	B b;
	A a;
};
//先调用父类的构造函数，再调用本身的构造函数，析构函数调用顺序反之
//先调用父类的构造函数，再调用成员对象的构造函数（成员对象的构造函数调用顺序和定义的顺序一样），
//最后再调用本身的构造函数，析构函数调用顺序反之

void test()
{
	Son s(10);
}

int main()
{
	test();

	system("pause");
	return 0;
}
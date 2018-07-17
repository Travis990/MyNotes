#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 虚析构函数是为了解决，父类指针指向子类对象，用父类指针删除子类对象

class Father
{
public:
	Father()
	{
		cout << "Father 的构造函数" << endl;
	}
	virtual void speak()
	{
		cout << "Father void speak()" << endl;
	}
	// 虚析构函数
	/*virtual ~Father()
	{
		cout << "Father 的析构函数" << endl;
	}*/

	// 纯虚析构函数
	virtual ~Father() = 0; // 有纯虚函数的类是抽象类
};

Father::~Father()
{
	cout << "Father 的析构函数" << endl;
}

class Son :public Father
{
public:
	Son()
	{
		cout << "Son 的构造函数" << endl;
	}
	virtual void speak()
	{
		cout << "Son void speak()" << endl;
	}
	~Son()
	{
		cout << "Son 的析构函数" << endl;
	}
};

void test()
{
	Father *f = new Son;
	f->speak();
	// 释放子类对象时，需要把父类的析构函数写成虚析构函数
	delete f;
}

int main()
{
	test();

	system("pause");
	return 0;
}
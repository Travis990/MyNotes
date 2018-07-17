#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//发生多态的三个条件
//1.要有继承
//2.要重写父类的虚函数
//3.要父类指针指向子类对象

class Father
{
public:
	// 虚函数
	virtual void info()
	{
		cout << "Father void info()" << endl;
	}
};

class Son1 :public Father
{
public:
	// 虚函数 virtual 可加可不加，
	virtual void info()
	{
		cout << "Son1 void info()" << endl;
	}
};

class Son2 :public Father
{
public:
	void info()
	{
		cout << "Son2 void info()" << endl;
	}
};

class Son3 :public Father
{
public:
	void info()
	{
		cout << "Son3 void info()" << endl;
	}
};

// 业务
void func(Father *father)
{
	father->info();
}

void test()
{
	Father *father = NULL;

	father = new Son1;
	func(father);

	father = new Son2;
	func(father);

	father = new Son3;
	func(father);
}

int main()
{
	test();

	system("pause");
	return 0;
}
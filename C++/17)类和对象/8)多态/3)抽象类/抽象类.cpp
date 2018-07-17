#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//有纯虚函数的类叫抽象类
//抽象类不能实例化对象
//注意：继承了抽象类，那么抽象类中的所有纯虚函数必须在子类中重写
//如果不重新，那么子类也会变为抽象类

class Father
{
public:
	//纯虚函数
	//返回值....
	//参数。。。
	virtual void getInfo1() = 0;
	virtual void getInfo2() = 0;
	virtual void getInfo3() = 0;
	virtual void getInfo4() = 0;
};

void test()
{
	//Father father; error
	Father *p;
}

class Son :public Father
{
public:
	// 虚函数 virtual 可加可不加，
	virtual void getInfo()
	{
		cout << "Son void getInfo()" << endl;
	}
};

// 注意：继承了抽象类，那么抽象类中的所有纯虚函数必须在子类中重写
void test2()
{
	//Son son; error
}

class Son2 :public Father
{
public:
	virtual void getInfo()
	{
		cout << "Son2 void getInfo()" << endl;
	}
	virtual void getInfo1()
	{

	}
	virtual void getInfo2()
	{

	}
	virtual void getInfo3()
	{

	}
	virtual void getInfo4()
	{

	}
};

void test3()
{
	Son2 son2;
}

int main()
{


	system("pause");
	return 0;
}
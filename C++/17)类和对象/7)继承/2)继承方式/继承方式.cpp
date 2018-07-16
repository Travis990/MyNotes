#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Father
{
public: // 公有
	int a;
private: // 私有
	int b;
protected: // 保护
	int c;
};
//公有继承
//类外可以访问从父类继承过来的公有权限成员
//类内可以访问从父类继承过来的公有权限成员
//类内可以访问从父类继承过来的保护权限成员
//类外不可以访问从父类继承过来的保护权限成员
//类内外都不能访问从父类继承过来的私有权限成员

class Son :public Father
{
	// 4个函数，3个变量

	void func()
	{
		a = 200;
		//b;
		c;
	}
};

void test01()
{
	Son s;
	s.a;
	s.Father::a;
}

//私有继承
//类外不能访问从父类继承过来的公有权限成员
//类内可以访问从父类继承过来的公有权限成员
//类外类内都不可以访问从父类继承过来的私有权限成员
//类内可以访问从父类继承过来的保护权限成员
//类外不可以访问从父类继承过来的保护权限成员

class Son2 :private Father
{
	//4个函数，3个变量

	void func()
	{
		a = 20;
		//b; error
		c;
	}
};

void test02()
{
	Son2 s2;
	//s2.a;  error
}

//保护继承
//类外不能访问从父类继承过来的公有权限成员
//类内可以访问从父类继承过来的公有权限成员
//类外类内都不可以访问从父类继承过来的私有权限成员
//类内可以访问从父类继承过来的保护权限成员
//类外不可以访问从父类继承过来的保护权限成员

class Son3 :protected Father
{
	void func()
	{
		a;
		//b; error
		c;
	}
};

void test03()
{
	Son3 s3;
	//s3.a; error
}

int main()
{


	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 自定义数据类型
struct Dejan_1 {
	// 1.结构体的默认权限为公有
	char name[64]; // 成员属性 (成员变量)
	int age;
	// 2.C++的结构体可以定义函数 (函数也叫方法)
	void func() // 成员函数 (成员方法)
	{
		cout << "func()" << endl;
	}
};

// 自定义数据类型 (类)
class Dejan_2 {
	// 1.类的默认权限为私有
	char name[64]; // 成员属性 (成员变量)
	int age;
	// 2.C++的结构体可以定义函数,类也可以
	void func()// 成员函数 (成员方法)
	{
		cout << "func()" << endl;
	}
};

int main()
{
	// 用类来实例化对象
	// 用自定义数据类型定义一个变量
	Dejan_2 dj2; // dj2就是对象

	// C++自定义类型变量,不需要加struct关键字
	Dejan_1 dj1;

	system("pause");
	return 0;
}
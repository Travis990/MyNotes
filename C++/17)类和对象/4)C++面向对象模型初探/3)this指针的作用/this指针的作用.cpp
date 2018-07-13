#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
//1.当成员变量和形参的名字一样时，用this指针来区分
//2.返回对象本身

class Girl
{
public:
	Girl(string name, int age)
	{
		this->name = name;
		this->age = age;
	}

	Girl& getObj()
	{
		return *this; // 返回的是对象，在运算符重载时有用
	}
public:
	string name;
	int age;
};

void test()
{
	Girl girl("小姐姐", 18);
	Girl &p = girl.getObj(); // 返回的对象是girl这个对象

	cout << &girl << endl;
	cout << &p << endl; // 两个地址是一样
}

int main()
{
	test();

	system("pause");
	return 0;
}
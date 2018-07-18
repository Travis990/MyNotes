#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Father
{
public:
	Father()
	{
		a = 100;
	}
public:
	int a;
};
// 从父类继承过来的同名成员被隐藏
class Son :public Father
{
public:
	Son()
	{
		a = 200;
	}
public:
	int a;
};

void test()
{
	Son s;
	cout << sizeof(Son) << endl; // 8
	cout << s.a << endl;
	// 通过父类的类名加作用域的方式来访问被隐藏的同名成员
	cout << s.Father::a << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
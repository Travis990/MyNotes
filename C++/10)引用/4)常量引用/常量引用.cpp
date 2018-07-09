#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	//int &p = 10; error:不是合法空间

	const int &p = 20;
	//编译器优化成:int tmp = 20;const int &p = tmp;
	cout << p << endl;

	//p = 300; error:p是常量不能赋值

	int a = 10;
	int &pa = a;
	pa = 200;

	system("pause");
	return 0;
}
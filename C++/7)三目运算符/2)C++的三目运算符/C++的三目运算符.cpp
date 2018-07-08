#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	int a = 10;
	int b = 20;
	(a > b ? a : b) = 100;
	cout << "a:" << a << endl; // 10
	cout << "b:" << b << endl; // 100
	// C++的三目运算符返回的是左值，返回的是空间

	system("pause");
	return 0;
}
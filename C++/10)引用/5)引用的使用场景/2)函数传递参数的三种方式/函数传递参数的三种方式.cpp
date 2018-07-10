#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
// 1.值传递
void func01(int a, int b) // int a=10,int b=20
{
	int tmp = a;
	a = b;
	b = tmp;
}
// 2.指针
void func02(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// 3.引用
void func03(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int a = 10;
	int b = 20;

	func01(a, b);
	cout << "func01() " << "a=" << a << "," << "b=" << b << endl; // 10 20
	func02(&a, &b);
	cout << "func02() " << "a=" << a << "," << "b=" << b << endl; // 20 10
	func03(a, b);
	cout << "func03() " << "a=" << a << "," << "b=" << b << endl; // 10 20

	system("pause");
	return 0;
}
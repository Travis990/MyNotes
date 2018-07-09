#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*  1.传参  */

// 指针实现1
void func(int *a)
{
	cout << *a << endl;
}
void test()
{
	int a = 10;
	func(&a);
}
// 引用实现1
void func2(int &a)
{
	cout << a << endl;  // 1.a 不用加 * 
}
void test2()
{
	int a = 10;
	func2(a); // 2.a 不需要 &
}

/*  2.给变量取别名 */
struct Dejan {};
void test3()
{
	// 申请合法的空间
	int a = 10;

	int &b = a; // 给a这块空间取别名为b
	b = 20;
	cout << "a=" << a << endl;

	int &c = b;
	c = 30;
	cout << "a=" << a << endl;
	cout << "-----------------------------------" << endl;
	cout << &a << endl;
	cout << &b << endl;
	cout << &c << endl;

	// 其他类型也一样
	double d = 20;
	double &p = d;

	Dejan dejan;
	Dejan &dj = dejan;
}

/*  引用的注意:  */
int func3()
{
	int a = 10;
	return a;
}
int* func4()
{
	int a = 10;
	return &a;
}
void test4()
{
	// 1.定义引用时，必须初始化
	int a = 10;
	//int &p3 = NULL; error

	int &p = a; // 定义时必须初始化

	// 2.引用一旦初始化，不能修改引用的指向
	int b = 20;
	p = b; // 这是赋值
	// &p = b; error
	cout << "&a=" << &a << endl;
	cout << "&p=" << &p << endl;

	// 3.必须引用一块合法的内存空间
	//int &p2 = func3(); // error: int &p2 = 10;
	//int &p2 = func4(); // error
}

int main()
{
	test4();

	system("pause");
	return 0;
}
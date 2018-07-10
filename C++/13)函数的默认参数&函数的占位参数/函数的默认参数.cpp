#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int myFunc(int a, int b=0) // 给函数的参数赋值，这参数就是函数的默认参数
{
	return a + b;
}

void test01() 
{
	// 如果没有给默认参数传值，那么函数就使用默认参数的值
	cout << myFunc(10)<<endl;
	// 如果有给默认参数传值，那么函数就优先使用用户传入的值
	cout << myFunc(20, 10) << endl;
}

// 函数的默认参数的注意:
// 1.在默认参数的右边必须都是默认参数
void myfunc2(int a, int b = 10, int c = 0, int d = 0)
{

}

// 2.声明和实现只能有一处有默认参数
void func(int a, int b);
void func(int a, int b = 0)
{

}

// 函数的占位参数,运算符重载的时候区分前置加加还是后置加加的时候有用
void func2(int a,int)
{

}
void test02() 
{
	func2(10,10);
}

int main()
{
	test01();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace Dejan
{
	int a = 10;
	int b = 20;
	int c = 30;
}

// using声明
void test_1()
{
	cout << Dejan::a << endl;
	using Dejan::b; // 声明命名空间中的b变量
	cout << b << endl;

	// 注意:从声明的行数以下不能再定义声明相同名字的变量
	// int b = 50;
}

// using编译指令
void test_2()
{
	using namespace Dejan; // using编译指令
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	// 如果是using编译指令, 那么就不存在重定义错误的问题
	int a = 20;
	int b = 30;
	int c = 40;
}

int main()
{
	cout << "using声明" << endl;
	test_1();
	cout << "using编译指令" << endl;
	test_2();

	system("pause");
	return 0;
}
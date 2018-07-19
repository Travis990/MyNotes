#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
// 5.函数模版和普通函数可以发生重载
int myplus(int a, int b)
{
	cout << "普通函数" << endl;
	return a + b;
}

template<class T>
T myplus(T a, T b)
{
	cout << "函数模板" << endl;
	return a + b;
}

// 6.函数模版之间也可以重载
template<class T>
T myplus(T a)
{
	cout << "函数模板" << endl;
	return a + 10;
}

void test01()
{
	int a = 10;
	int b = 20;
	myplus(a, b); // 1.当函数模版和普通函数重载，优先调用普通函数

	myplus(20.22, 10.11); // 2.但是你传入参数类型和普通函数不匹配时，调用函数模版

	myplus(a, 'c'); // 3.字符类型会隐式转换成int类型

	// 4.强制调用函数模版
	myplus<>(a, b); // <>空参数列表
}

// 强制调用函数模版的隐式转换
template<class T>
T func(T a, T b)
{
	return a + b;
}

void test02()
{
	// 隐式的转换
	cout << func<int>(3, 3.5) << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
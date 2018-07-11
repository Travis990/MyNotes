#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	// 按照参数来分类
	// 无参构造函数
	Dejan()
	{
		cout << "无参构造" << endl;
	}
	// 有参构造函数
	Dejan(int a)
	{
		cout << "有参构造" << endl;
	}

	// 按照类型来分
	// 普通构造
	// 拷贝构造
	Dejan(const Dejan &d) // 1.拷贝构造函数中的形参中的引用一定要加
	{
		cout << "拷贝构造" << endl;
	}
};

void test()
{
	Dejan dejan; // 调用无参构造
	Dejan dejan2(10); // 调用有参构造
	Dejan dejan3(dejan); // 调用拷贝构造函数

	//Dejan dejan4 = dejan; // 调用拷贝构造函数
	// 如果拷贝默认函数的参数不为引用将导致如下的死循环
	/*
	Dejan(const Dejan d) // Dejan d = dejan;//调用拷贝构造函数
	Dejan(const Dejan d) // Dejan d = dejan;//调用拷贝构造函数
	Dejan(const Dejan d) ......
	*/
}

// 2.调用有参和拷贝构造函数
// 调用有参构造
void test02()
{
	// 1.括号法
	Dejan dejan(10); // (常用)
	// 2.显示的调用有参构造
	Dejan dejan2 = Dejan(10);
	// 3.等号法
	Dejan dejan3 = 10; // 编译器优化成：Dejan dejan3 = Dejan(10);
}

// 调用拷贝构造
void test03()
{
	Dejan dejan;
	Dejan dejan2(dejan); // 调用拷贝构造(常用)
	Dejan dejan3 = Dejan(dejan); // 调用拷贝构造
	Dejan dejan4 = dejan; // 调用拷贝构造 编译器优化: Dejan dejan4 = Dejan(dejan);
}

int main()
{
	test03();

	system("pause");
	return 0;
}
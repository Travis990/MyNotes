#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	// 防止隐式转换 explicit只能修饰构造
	Dejan(int n)
	{
		cout << "有参构造" << endl;
	}
	// 多参构造函数
	explicit Dejan(int a, int b = 0, int c = 0)
	{
		cout << "多参构造" << endl;
	}
};

void test()
{
	Dejan dejan = 10; // 编译器优化成：Dejan dejan=Dejan(10);
	Dejan dejan2(10,20); // 注意:多参构造如果除了第一个参数没有默认值其他都有默认值情况下, 如果前面定义了单一参数构造函数将会导致编译器无法选择
	// explicit Dejan(int n)  // 如构造函数前加了 explicit修饰,对象初始化时将不允许以赋值形式传参给构造函数
	// Dejan dejan = 10; error: 禁止隐式转换
}

int main()
{
	test();

	system("pause");
	return 0;
}
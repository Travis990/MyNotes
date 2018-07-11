#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		age = 0;
		cout << "无参构造" << endl;
	}
	Dejan(int age)
	{
		this->age = age;
		cout << "有参构造函数" << endl;
	}
	Dejan(const Dejan &dejan)
	{
		cout << "拷贝构造" << endl;
	}
public:
	int age;
};

// 2.对象以值的方式传递时会调用拷贝构造
void func(Dejan dejan) // Dejan dejan = d1
{

}

void test()
{
	Dejan d1; // 调用无参构造

	// 1.用已有的对象去初始化另一个对象
	Dejan d2(d1);

	func(d1);
}

// 3.函数返回局部对象时，vs debug模式会调用一次拷贝构造
// 在release模式下，不调用拷贝构造，编译器会优化，把函数内的局部对象保留
// qt编译器也一样，不会调用拷贝构造
Dejan func2()
{
	Dejan dejan;
	cout << "dejan:" << &dejan << endl;
	return dejan;
}

void test02() // vs轮流切换下"Debug"、"Release"模式观察结果变化, 总结: 自定义类型函数局域中返回该参数同类型的对象,在vs的debug模式下编译器会进行拷贝再返回拷贝副本给左值,在"Release"模式下编译器会进行保留即该局域中返回的对象不会被释放直接给了左值指向
{
	Dejan d2 = func2();
	cout << "d2:" << &d2 << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
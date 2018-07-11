#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		cout << "无参构造函数" << endl;
	}
	Dejan(int a)
	{
		cout << "有参构造函数" << endl;
	}
	Dejan(const Dejan &d)
	{
		cout << "拷贝构造函数" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
};

// 1.匿名对象的生命周期仅在本行
void test01()
{
	Dejan(); // 匿名对象，在栈解旋的时候有用
	Dejan(10); // 匿名对象，调用有参构造
	cout << "匿名对象还在吗?" << endl;
}

// 2.匿名对象不能调用拷贝构造函数
void test02()
{
	Dejan dejan;
	//Dejan(dejan); error:重定义,编译器把这句代码看成 Dejan dejan;
}

int main()
{
	test01();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		a = 10;
		b = 20;
	}
public:
	static int a; // 静态成员变量
	int b;
private:
	static int c;
};
//类外
int Dejan::a = 100;
//1.静态成员变量属于类，不属于对象
//2.静态成员变量必须在类内声明，在类外初始化
//3.静态成员变量可以用类来访问，也可以用对象来访问
//4.静态成员变量的生命周期在程序结束，他的作用域是在类内

void test()
{
	cout << Dejan::a << endl;

	// 1.分配空间，2，调用构造函数
	Dejan d;
	cout << d.a << endl;

	//Dejan *p = new Dejan[10];
}

int main()
{
	test();

	system("pause");
	return 0;
}
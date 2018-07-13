#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{

	}
public:
	const int a = 10;
	// const修饰的静态成员变量最好在类内初始化
	// const static int b=200; // const修饰的静态成员变量
	const static int b;
};

const int Dejan::b = 300;

void test()
{
	Dejan d;
	cout << Dejan::b << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
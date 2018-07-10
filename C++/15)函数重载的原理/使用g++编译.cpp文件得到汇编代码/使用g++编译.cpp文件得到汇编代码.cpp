#include<iostream>
using namespace std;
// 编译器给这些函数取别名来区分是哪个函数
void func(int a)
{

}

void func(int a, int b)
{

}
void func(double a)
{

}

void func(double a, int b)
{

}
void func(int a, double b)
{

}

int main()
{


	system("pause");
	return 0;
}
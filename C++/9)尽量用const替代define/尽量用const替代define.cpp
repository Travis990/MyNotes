#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define NUM 128
//1.用宏定义的没有类型
//2.宏的作用域是整个文件
const short num = 128;

void func(short a)
{
	cout << "func(short a)" << endl;
}

void func(int a) 
{
	cout << "func(int a)" << endl;
}

int main()
{
	func(num);

	system("pause");
	return 0;
}
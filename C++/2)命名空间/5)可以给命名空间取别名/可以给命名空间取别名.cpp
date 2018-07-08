#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//注意5：可以给命名空间取别名
namespace A
{
	int a = 10;
	int b = 20;
}

int main()
{
	//B 新名字    A 旧名字
	namespace B = A;
	cout << B::a << endl;
	cout << B::b << endl;

	system("pause");
	return 0;
}
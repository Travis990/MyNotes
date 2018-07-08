#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = 10;
	int b = 20;
	printf("%d\n", a > b ? a : b);

	//(a > b ? a : b) = 100; error

	//(a > b ? a : b) = 100;C语言的三目运算符返回的不是左值，返回的不是空间，返回的是值
	//等号的左边就叫左值，等号的右边就叫右值
	//左值是可以修改的，有空间的

	//(a > b ? a : b) 返回的20
	//20 = 100;

	system("pause");
	return 0;
}
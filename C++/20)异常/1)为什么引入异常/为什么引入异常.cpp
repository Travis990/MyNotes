#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1.返回值不明确，没有语言信息
//2.返回值可以忽略
//3.只能返回一个信息
int func(int *p)
{
	if (NULL == p)
	{
		return -1;
	}
	return 0;
}

void test()
{
	int *p = NULL;
	func(p);
}

int main()
{
	test();

	system("pause");
	return 0;
}
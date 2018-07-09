#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 建立数组的引用
void test()
{
	int arr[] = { 1, 2, 3, 4, 5 };

	// 第一种方法
	typedef int(ARRAY)[5]; // 定义数组类型
	ARRAY &ret = arr;
	/*
	int a = 10;
	int &p = a;
	*/
	// 第二种方法(常用)
	int(&ARR_RET)[5] = arr;
	/*
	int a = 10;
	int &p = a;
	*/
	// 第三种方法
	typedef int(&ARRAY2)[5]; // 定义引用数组类型
	ARRAY2 ret2 = arr;


	for (int i = 0; i < 5; i++)
	{
		ret[i] = 100 + i;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << ret2[i] << " ";
	}
	cout << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	// 申请堆区空间时,必须要详细的强制转换类型
	//char *p = malloc(50);  error 
	char *p = (char*)malloc(50);

	system("pause");
	return 0;
}
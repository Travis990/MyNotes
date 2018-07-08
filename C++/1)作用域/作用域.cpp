#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int a = 10;

int main()
{
	int a = 20;
	// 就近原则
	cout << a << endl;
	cout << ::a << endl;

	system("pause");
	return 0;
}
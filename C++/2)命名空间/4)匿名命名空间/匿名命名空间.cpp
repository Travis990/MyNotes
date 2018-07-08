#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//注意4:匿名命名空间
namespace {
	int coun = 0;
}

int main()
{
	cout << ::coun << endl;

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		a = 10;
	}

	void func()const
	{
		//const修饰的是this指针指向的空间
		//让这个空间中的值不能修改
		//a = 100;
	}
public:
	int a;
};

int main()
{


	system("pause");
	return 0;
}
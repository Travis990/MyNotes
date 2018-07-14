#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan(int a)
	{
		this->a = a;
	}
	//Dejan d();   m - 5

	Dejan operator-(int val)
	{
		Dejan tmp(this->a - val);
		return tmp;
	}
public:
	int a;
};

int operator-(int val, Dejan &d)
{
	int ret = val - d.a;
	return ret;
}

void test()
{
	Dejan d(10);
	Dejan d2 = d - 5;

	cout << "d2.a=" << d2.a << endl;

	int ret = 20 - d;
	cout << "ret=" << ret << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
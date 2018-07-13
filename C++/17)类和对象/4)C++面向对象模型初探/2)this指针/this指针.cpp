#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	void printDejan()
	{
		cout << this->a << " " << this->b << endl;
	}
public:
	int a;
	int b;
};
// thisÖ¸ÕëÊÇconst this

void test()
{
	Dejan d1(10, 20);
	d1.printDejan();
	Dejan d2(30, 60);
	d2.printDejan();
	Dejan d3(100, 200);
	d3.printDejan();
}

int main()
{
	test();

	system("pause");
	return 0;
}
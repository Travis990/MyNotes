#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		a = 100;
	}
public:
	int a;
};

istream& operator >> (istream &in, Dejan &d)
{
	in >> d.a;
	return in;
}

void test()
{
	Dejan dejan;
	cin >> dejan;

	cout << dejan.a << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

void test()
{
	pair<string, int> mypair("AAA", 10);
	cout << mypair.first << " " << mypair.second << endl;

	pair<int, int> mypair2(10, 20);
	cout << mypair2.first << " " << mypair2.second << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Dejan
{
	// 让这个全局函数成为Dejan类友元函数
	friend void func(Dejan &dejan);
public:
	Dejan(string name)
	{
		this->name = name;
	}
private:
	string name;
};

// 全局函数
void func(Dejan &dejan)
{
	cout << dejan.name << endl;
}

void test()
{
	Dejan dejan("小哥哥");
	func(dejan);
}

int main()
{
	test();

	system("pause");
	return 0;
}
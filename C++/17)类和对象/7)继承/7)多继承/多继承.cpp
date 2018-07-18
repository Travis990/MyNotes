#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class FatherA
{
public:
	FatherA()
	{
		CarName = "宝马";
	}
public:
	string CarName;
};

class FatherB
{
public:
	FatherB()
	{
		CarName = "宝马";
	}
public:
	string CarName;
};

class Son :public FatherA, public FatherB
{

};
// 多继承中同名问题不能解决

void test()
{
	Son s;
	//s.CarName; error
	cout << s.FatherA::CarName << endl;
	cout << s.FatherB::CarName << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
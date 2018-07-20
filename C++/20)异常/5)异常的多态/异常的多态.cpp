#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Father
{
public:
	virtual void speak() {}
};

class Son :public Father
{
public:
	virtual void speak()
	{
		cout << " Son void speak()" << endl;
	}
};

class Son1 :public Father
{
public:
	virtual void speak()
	{
		cout << " Son1 void speak()" << endl;
	}
};

void func()
{
	//throw Son();
	throw Son1();
}

void test()
{
	//Father *f = new Son;

	try
	{
		func();
	}
	catch (Father &e) // Father &e = Son()
	{
		cout << "捕获一个Son类型的异常" << endl;
		e.speak();
	}
}

int main()
{
	test();

	system("pause");
	return 0;
}
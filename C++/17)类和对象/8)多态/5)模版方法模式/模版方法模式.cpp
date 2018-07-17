#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Drink
{
public:
	// 煮水
	virtual void func1() = 0;
	// 冲泡
	virtual void func2() = 0;
	// 导入容器
	virtual void func3() = 0;
	// 加点辅料
	virtual void func4() = 0;

	void maker()
	{
		func1();
		func2();
		func3();
		func4();
	}
};

class Coffee :public Drink
{
	// 煮水
	virtual void func1()
	{
		cout << "煮点开水" << endl;
	}
	// 冲泡
	virtual void func2()
	{
		cout << "冲泡咖啡" << endl;
	}
	// 导入容器
	virtual void func3()
	{
		cout << "倒入杯中" << endl;
	}
	// 加点辅料
	virtual void func4()
	{
		cout << "加点糖或牛奶" << endl;
	}

	/*
	void maker()
	{
		func1();
		func2();
		func3();
		func4();
	}
	*/
};

void test()
{
	Drink *drink = NULL;
	drink = new Coffee;
	drink->maker();
	delete drink;
}

int main()
{
	test();

	system("pause");
	return 0;
}
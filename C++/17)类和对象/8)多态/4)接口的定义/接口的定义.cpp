#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Father
{
public:
	//纯虚函数
	//返回值....
	//参数。。。
	virtual void getInfo() = 0; // 接口

	virtual void getInfo2() = 0;
	virtual void getInfo3() = 0;
	virtual void getInfo4() = 0;
};

class Son :public Father
{
	virtual void getInfo()
	{
		cout << "Son void getInfo()" << endl;
	}

	virtual void getInfo2()
	{
		cout << "Son void getInfo2()" << endl;
	}

	virtual void getInfo3()
	{
		cout << "Son void getInfo3()" << endl;
	}

	virtual void getInfo4()
	{
		cout << "Son void getInfo4()" << endl;
	}
};

void func(Father *father)
{
	father->getInfo();
}

void test()
{
	Father *father = NULL;
	father = new Son;
	func(father);
}

int main()
{
	test();

	system("pause");
	return 0;
}
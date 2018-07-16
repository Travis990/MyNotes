#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan()
	{
		a = 0;
	}
	// 重载bool,没有返回值
	operator bool()
	{
		if (a <= 0)
		{
			return false;
		}
		return true;
	}
	operator int()
	{
		return 10;
	}
public:
	int a;
};

void test()
{
	Dejan dejan;
	if (!dejan)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
	int ret = (int)dejan;
	cout << "ret=" << ret << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
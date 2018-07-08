#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace Girl {
	int a = 18;
	int b = 20;
	int c = 23;
	void girl_1()
	{
		cout << "小姐姐1,身高165,偏瘦。" << endl;
	}
	void girl_2()
	{
		cout << "小姐姐2,身高175,微胖。" << endl;
	}
}

int a = 30;

int main()
{
	cout << "在校时的女同学:" << Girl::a << endl;
	cout << "公司里的女同事:" << a << endl;
	cout << "我喜欢的类型↓" << endl;
	Girl::girl_2();

	system("pause");
	return 0;
}
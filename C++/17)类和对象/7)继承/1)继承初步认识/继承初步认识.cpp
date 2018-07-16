#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//继承：1.代码复用。2.扩展类的功能
//父类（基类）

class Father
{
public:
	void func1()
	{
		cout << "小姐姐" << endl;
	}
	void func2()
	{
		cout << "我要改签" << endl;
	}
	void func3()
	{
		cout << "你要去哪里?" << endl;
	}
	void func4()
	{
		cout << "我要去你心里" << endl;
	}
};

// 子类（派生类） 
class Son :public Father // 共有继承
{
public:
	void Sonfunc1()
	{
		cout << "小姐姐, 奶茶能加什么?" << endl;
	}
	void Sonfunc2()
	{
		cout << "能加珍珠, 椰果" << endl;
	}
	void Sonfunc3()
	{
		cout << "能加你微信吗?" << endl;
	}
};

void test()
{
	Son s;
	s.func1();
	s.func2();
	s.func3();
	s.func4();
	s.Sonfunc1();
	s.Sonfunc2();
	s.Sonfunc3();
}

int main()
{
	test();

	system("pause");
	return 0;
}
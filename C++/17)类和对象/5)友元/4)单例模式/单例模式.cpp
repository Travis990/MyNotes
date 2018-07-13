#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

//类只能实例化一个对象
//1.让无参构造函数私有化
//2.定义一个静态成员变量（类的指针）
//3.在类外new一个对象给这个指针
//4.为了防止用户在类外把这个指针置空，那么把这个指针设置为私有，
//再提供一个获取这个指针的静态成员函数
//5.因为拷贝构造函数调用时也会生成新的对象，这时把拷贝构造函数也私有化

class Dejan
{
public:
	static Dejan *getObj() // 静态成员函数
	{
		return p;
	}
private:
	Dejan() {}
	Dejan(const Dejan &dejan)
	{
		cout << "拷贝构造函数" << endl;
	}
private:
	static Dejan* p; // 声明一个静态成员变量
};
Dejan* Dejan::p = new Dejan; // 给一个对象

void test()
{
	Dejan *myp = Dejan::getObj();
	Dejan *myp2 = Dejan::getObj();
	Dejan *myp3 = Dejan::getObj();
	Dejan *myp4 = Dejan::getObj();

	cout << "myp=" << myp << endl;
	cout << "myp2=" << myp2 << endl;
	cout << "myp3=" << myp3 << endl;
	cout << "myp4=" << myp4 << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
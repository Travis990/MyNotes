#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

template<class T1, class T2>
class Dejan
{
public:
	Dejan(T1 Name, T2 Age)
	{
		name = Name;
		age = Age;
	}
	//友元函数在类内实现
	//友元函数不属于类，不是类的成员函数
	friend void printDejan(Dejan<T1, T2> &d)
	{
		cout << "name:" << d.name << " age:" << d.age << endl;
	}
private:
	T1 name;
	T2 age;
};

void test()
{
	Dejan<string, int> d("小哥哥", 18);
	printDejan(d);
}

// 4.把类的声明放到函数模版声明的前面
template<class T1, class T2>
class Maker;

// 3.把函数模版的声明放到类的前面
template<class T1, class T2>
void printMaker(Maker<T1, T2> &m);

template<class T1, class T2>
class Maker
{
public:
	Maker(T1 Name, T2 Age)
	{
		name = Name;
		age = Age;
	}
	//2.加上空参数列表来强制调用函数模版
	friend void printMaker<>(Maker<T1, T2> &m);
private:
	T1 name;
	T2 age;
};



// 1.把友元函数写成函数模版
template<class T1, class T2>
void printMaker(Maker<T1, T2> &m)
{
	cout << "name:" << m.name << " age:" << m.age << endl;
}

void test02()
{
	Maker<string, int> m("小哥哥", 20);
	printMaker(m);
}

int main()
{
	test02();

	system("pause");
	return 0;
}
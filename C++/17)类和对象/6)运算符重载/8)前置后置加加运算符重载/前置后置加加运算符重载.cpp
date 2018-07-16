#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan(int a)
	{
		this->a = a;
	}
	// 前置加加, 返回的是引用
	Dejan& operator++()
	{
		++a;
		return *this;
	}
	// 后置加加，先返回，后加加  返回的是值
	// 后置加加, 返回的是新对象
	Dejan operator++(int) // 占位参数必须是int
	{
		// d++
		// *this里面的a是多少？15
		Dejan tmp(*this); // 调用了什么构造函数，拷贝构造函数
		++this->a; // 后加加,*this是d
		return tmp;
	}
public:
	int a;
};

ostream& operator<<(ostream &out, Dejan &d)
{
	out << d.a;
	return out;
}

//同等条件下，优先使用前置加加，因为后置加加需要实例化一个临时变量，而且需要调用两次拷贝构造函数

// 1.前置加加，先加加再返回
void test()
{
	Dejan d(10);
	cout << ++d << endl;
}

// 2.后置加加，先返回，后加加
void test2()
{
	Dejan d(15);
	cout << d++ << endl;
	cout << d << endl;
}

int main()
{
	test2();

	system("pause");
	return 0;
}
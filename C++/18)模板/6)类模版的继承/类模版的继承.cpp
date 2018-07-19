#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
// 普通类继承类模版
template<class T1>
class Father
{
public:
	T1 a;
};
// 继承时，必须告诉编译器父类的T1具体是什么数据类型
class Son :public Father<int>
{
public:

};

void test01()
{
	Son s;
}

// 类模版继承类模版
template<class T, class T2>
class Son2 :public Father<T2> // 可以晚一点告诉编译器父类的T1是什么类型
{
public:
	T age;
};

void test02()
{
	Son2<int, string> s2;
}

//类模版的继承需要注意：必须告诉编译器，父类的参数化的数据类型是什么类型
int main()
{


	system("pause");
	return 0;
}
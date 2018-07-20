#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 静态转换
// 1)基础数据类型
void test01()
{
	char a = 'a';

	// char  -->  double    static_cast关键字<要转换到的类型>（谁要转换）
	double d = static_cast<double>(a);
	cout << d << endl;
}

// 2)自定义数据类型
class Father {};
class Son :public Father {};
class Dejan {};
void test02()
{
	// 1.指针
	Father *f = NULL;
	Son *s = NULL;
	// 向下转换,不安全
	Son *s1 = static_cast<Son*>(f);
	// 向上转换,安全
	Father *f1 = static_cast<Father*>(s);

	// 2.引用
	Father F;
	Son S;
	Father &F1 = F;
	Son &S1 = S;
	// 向下转换,不安全
	Son& S2 = static_cast<Son&>(F1);
	// 向上转换,安全
	Father& F2 = static_cast<Father&>(S1);
}

// 动态转换
void test03()
{
	/*char a = 'a';  error: 基础数据类型不能用动态转换
	double d = dynamic_cast<double>(a);*/

	Father *f = NULL;
	Son *s = NULL;

	// 向上转换,安全
	Father *f1 = dynamic_cast<Father*>(s);

	// 向下转换，不安全,会检测
	//Son *s1 = dynamic_cast<Son*>(f); error
}

// 常量转换
void test04()
{
	const int *p = NULL;
	// const  ---> 非const
	int *newp = const_cast<int*>(p);

	int *pp = NULL;
	// 非const  ---> const
	const int *newpp = const_cast<const int*>(pp);
}

// 重新解释转换
void test05()
{
	int a = 10;
	int *p = reinterpret_cast<int*>(a);

	Father *f = NULL;
	Dejan *d = reinterpret_cast<Dejan*>(f);
}

int main()
{
	test01();

	system("pause");
	return 0;
}
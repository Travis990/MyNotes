#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

// 类模板
template<class NameType, class AgeType>
class Dejan
{
public:
	Dejan(NameType name, AgeType age)
	{
		this->name = name;
		this->age = age;
	}
	void printDejan()
	{
		cout << "name:" << this->name << " age:" << this->age << endl;
	}
public:
	NameType name;
	AgeType age;
};

void test()
{
	// 类模版不能自动推导数据类型，必须显示告诉编译器具体类型是什么
	Dejan<string, int> m1("小哥哥", 18);
	m1.printDejan();

	Dejan<int, int> m2(10, 20);
	m2.printDejan();

	//Dejan<> m3(10,0); error
}

// 类模版可以有默认的参数，参数是数据类型(默认参数后面的参数必须都是默认参数)
template<class NameType, class AgeType = int, class T = double>
class Dejan2
{
public:
	Dejan2(NameType name, AgeType age)
	{
		this->name = name;
		this->age = age;
	}

	void printDejan2()
	{
		cout << "name:" << this->name << " age:" << this->age << endl;
	}
public:
	NameType name;
	AgeType age;
};

void test02()
{
	Dejan2<string, int, double> m1("小姐姐", 20);
	m1.printDejan2();
	// 优先使用用户传入数据类型
	Dejan2<string, double, int> m2("小姐姐", 20.38);
	m2.printDejan2();
}

// 有默认参数的类模版传参注意：
void test03()
{
	// 如果类模版有默认参数，那么参数列表中可以不指定数据类型
	Dejan2<string> d("小姐姐", 18);
	// 如果你传入具体数据和默认的数类型不同时，编译器会尝试转换，
	// 如果转换成功，就OK，如果转换不成功就报错
	Dejan2<string> d2("小姐姐", 18.66);
	d2.printDejan2();
	/*Dejan2<string> d3("小姐姐","aaa"); error
	d3.printDejan2();*/
}

// int N 是非类型参数
template<class NameType, class AgeType = int, class T = double, int N = 20>
class Dejan3
{
public:
	Dejan3(NameType name, AgeType age)
	{
		this->name = name;
		this->age = age;
	}

	void printDejan3()
	{
		cout << "name:" << this->name << " age:" << this->age << " N:" << N << endl;
	}
public:
	NameType name;
	AgeType age;
};

void test04()
{
	Dejan3<string, int, double, 10> m("小姐姐", 18);
	m.printDejan3();
}

// 用类做为类模版的参数
class Dejan51
{
public:
	void printDejan51()
	{
		cout << "printDejan51()" << endl;
	}
};

class Dejan52
{
	void printDejan52()
	{
		cout << "printDejan52()" << endl;
	}
};

template<class T>
class myClass
{
public:
	T obj;

	void func1()
	{
		obj.printDejan51();
	}
	void func2()
	{
		obj.printDejan52();
	}
};

void test05()
{
	myClass<Dejan51> m;
	m.func1();
	//m.func2();   error
	/*
	class myClass
	{
	public:
		Dejan51 obj;

		void func1()
		{
			obj.printDejan51();
		}

		void func2()
		{
			obj.printDejan52();
		}
	};
	*/
}

int main()
{
	test05();

	system("pause");
	return 0;
}
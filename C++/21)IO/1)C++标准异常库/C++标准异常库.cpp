#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stdexcept> // 异常库的头文件，vs2013不需要
using namespace std;

// 1.使用标准异常库
class Dejan
{
public:
	Dejan(int age)
	{
		if (age < 0 || age >180)
		{
			throw out_of_range("年龄超出正常范围");
		}
		else
		{
			this->age = age;
		}
	}
public:
	int age;
};

void test()
{
	try
	{
		Dejan(200);
	}
	catch (out_of_range &e)
	{
		cout << e.what() << endl;
	}
}

// 2.自定义异常类
class myOut_of_range :public exception
{
public:
	myOut_of_range(const char *str)
	{
		//const char*--->string
		this->err_msg = string(str);
	}
	myOut_of_range(const string str)
	{
		this->err_msg = str;
	}
	virtual const char* what() const
	{
		//string  ->const char*
		return this->err_msg.c_str();
	}
public:
	string err_msg;
};

class Maker
{
public:
	Maker(int age)
	{
		if (age < 0 || age >180)
		{
			throw myOut_of_range("自己的异常类: 年龄超出正常范围");
		}
		else
		{
			this->age = age;
		}
	}
public:
	int age;
};

void test2()
{
	try
	{
		Maker(200);
	}
	catch (myOut_of_range &e)
	{
		cout << e.what() << endl;
	}
}

int main()
{
	test2();

	system("pause");
	return 0;
}
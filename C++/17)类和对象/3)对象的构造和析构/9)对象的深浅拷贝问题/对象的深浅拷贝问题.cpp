#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
// 默认的拷贝构造函数做了什么?做了简单的赋值操作

class Dejan
{
public:
	Dejan()
	{
		a = 0;
		b = 0;
	}
	Dejan(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
public:
	int a;
	int b;
};

void test()
{
	Dejan dejan(10, 20); // 调用有参构造
	Dejan dejan2(dejan); // 调用默认拷贝构造函数
	cout << "dejan.a=" << dejan.a << " dejan.b=" << dejan.b << endl;
	cout << "dejan2.a=" << dejan2.a << " dejan2.b=" << dejan2.b << endl;

	/*
	默认构造函数做了简单的赋值操作
	dejan2.a = dejan.a;
	dejan2.b = dejan.b;
	*/
}

class Girl
{
public:
	Girl()
	{

	}
	Girl(const char *name, int age) // 有参构造
	{
		this->age = age;
		this->name = (char*)malloc(strlen(name) + 1);
		strcpy(this->name, name);
	}

	Girl(const Girl &girl)
	{
		cout << "女孩的拷贝构造函数" << endl;
		this->name = (char*)malloc(strlen(girl.name) + 1);
		strcpy(this->name, girl.name);
		this->age = girl.age;
	}
	// 重写赋值函数时

	void printGirl()
	{
		cout << "name:" << name << " age:" << age << endl;
	}
	~Girl() {
		if (NULL != name)
		{
			free(name);
			name = NULL;
		}
	}
public:
	char *name;
	int age;
};

void test02()
{
	Girl girl("小姐姐", 16);
	girl.printGirl();

	Girl girl2(girl); // 调用默认的拷贝构造函数
	cout << girl2.name << " " << girl2.age << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
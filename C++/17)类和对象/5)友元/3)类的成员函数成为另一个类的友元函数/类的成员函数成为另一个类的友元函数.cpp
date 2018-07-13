#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

// 声明类
class Girl;
class Student
{
public:
	void func(Girl &girl);
};

class Girl
{
	// 让类的成员函数成为另一个类的友元函数
	friend void Student::func(Girl &girl); // Student的成员函数
public:
	Girl(string name)
	{
		this->name = name;
	}
private:
	string name;
};

void Student::func(Girl &girl)
{
	cout << girl.name << endl;
}

void test()
{
	Girl girl("小姐姐");

	Student s;
	s.func(girl);
}

int main()
{
	test();

	system("pause");
	return 0;
}
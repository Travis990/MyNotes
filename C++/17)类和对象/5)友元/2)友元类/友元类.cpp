#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Girl
{
	// 让Student类成为Girl类的友元类
	friend class Student;
public:
	Girl(string name)
	{
		this->name = name;
	}
private:
	string name;
};

// 让类成为另一类的友元类
class Student
{
public:
	void func(Girl &girl)
	{
		cout << girl.name << endl;
	}
};

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
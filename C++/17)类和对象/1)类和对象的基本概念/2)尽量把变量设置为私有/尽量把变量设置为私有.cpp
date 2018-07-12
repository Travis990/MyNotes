#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Dejan
{
private:
	string name;
	int func;
	int age;
public:
	void setName(string Name)
	{
		name = Name;
	}
	void setFunc(int Func)
	{
		func = Func;
	}
	void setAge(int Age)
	{
		age = Age;
	}

	int getAge()
	{
		return age;
	}
	void test()
	{
		cout << func << endl;
	}
};

int main()
{
	Dejan dejan;
	dejan.setAge(18);
	dejan.setFunc(20);
	dejan.setName("Ð¡½ã½ã");

	dejan.test();
	cout << dejan.getAge() << endl;

	system("pause");
	return 0;
}
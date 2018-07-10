#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Student
{
public:
	// 设置姓名的方法
	void setName(string Name)
	{
		name = Name;
	}
	// 设置id的方法
	void setID(int Id)
	{
		id = Id;
	}
	// 打印姓名和id的方法
	void printStudent()
	{
		cout << "name:" << name << " id:" << id << endl;
	}
public:
	string name;
	int id;
};

int main()
{
	Student s;
	s.setName("小姐姐");
	s.setID(1);
	s.printStudent();

	cout << s.name << " " << s.id << endl;

	system("pause");
	return 0;
}
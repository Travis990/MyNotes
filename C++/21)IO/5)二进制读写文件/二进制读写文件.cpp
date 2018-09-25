#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Maker
{
public:
	Maker()
	{}
	Maker(const char*name, int age)
	{
		strcpy(this->name, name);
		this->age = age;
	}
public:
	//读写对象时，不要在类中写string类型的变量
	//string name;
	/*
	原因一：
	string容器分配空间的策略：16个字节在栈区，大于16个字节在堆区（string内部有一个指针，指向堆区空间）
	文件写
	原因二：
	指针写入文件会无效
	*/

	char name[64];
	int age;
};

void test01()
{
	Maker m1("悟空", 18);
	Maker m2("贝吉塔", 20);

	ofstream ofs;
	ofs.open("test.txt", ios::out | ios::trunc | ios::binary);
	if (!ofs.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	//写对象
	ofs.write((const char *)&m1, sizeof(Maker));
	ofs.write((const char *)&m2, sizeof(Maker));

	ofs.close();
}

void test02()
{
	Maker m1;
	Maker m2;

	ifstream ifs;
	ifs.open("test.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	//读对象
	ifs.read((char*)&m1, sizeof(Maker));
	ifs.read((char*)&m2, sizeof(Maker));

	ifs.close();

	cout << "name:" << m1.name << " age" << m1.age << endl;
	cout << "name:" << m2.name << " age" << m2.age << endl;
}

int main()
{
	test02();

	system("pause");
	return EXIT_SUCCESS;
}


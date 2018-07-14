#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
public:
	Dejan(const char *name)
	{
		// 从堆区申请空间
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	// d1 = d2
	Dejan& operator=(const Dejan &dejan)
	{
		// 1.释放原来的空间
		if (NULL != this->name)
		{
			delete[] this->name;
			this->name = NULL;
		}
		// 2.申请新的空间
		this->name = new char[strlen(dejan.name) + 1];
		// 3.拷贝数据
		strcpy(this->name, dejan.name);
		// 返回对象本身
		return *this;
	}
	void printDejan()
	{
		cout << this->name << endl;
	}
	~Dejan()
	{
		if (NULL != this->name)
		{
			delete[] this->name;
			this->name = NULL;
		}
	}
public:
	char *name;
};

void test()
{
	Dejan d1("小哥哥");
	Dejan d2("小姐姐");

	d1.printDejan();
	d2.printDejan();

	d1 = d2;

	d1.printDejan();
	d2.printDejan();
}

int main()
{
	test();

	system("pause");
	return 0;
}
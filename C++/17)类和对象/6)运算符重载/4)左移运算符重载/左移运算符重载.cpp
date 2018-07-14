#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Dejan
{
	friend ostream& operator<<(ostream &out, Dejan &d);
public:
	Dejan()
	{
		age = 18;
	}
private:
	int age;
};

// ostream把拷贝构造函数私有化了，所以这里不能返回值，返回值需要调用拷贝构造函数
ostream& operator<<(ostream &out, Dejan &d)
{
	out << d.age;
	return out;
}

int main()
{
	//basic_ostream
	Dejan d;
	cout << d << endl;

	int a = 10;
	cout << a;

	system("pause");
	return 0;
}
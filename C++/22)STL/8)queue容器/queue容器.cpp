#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<string>
using namespace std;

// 先进先出
void test01()
{
	queue<int> q;
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);
	q.push(50);

	cout << q.front() << endl;
	cout << q.back() << endl;
	cout << endl;
	while (!q.empty())
	{
		cout << q.front() << endl;
		q.pop();
	}

	cout << "size:" << q.size() << endl;
}

// 2.存储对象
class Dejan
{
public:
	Dejan(string name, int age)
	{
		this->name = name;
		this->age = age;
	}
public:
	string name;
	int age;
};

void test02()
{
	queue<Dejan> q;
	q.push(Dejan("aaa1", 10));
	q.push(Dejan("aaa1", 20));
	q.push(Dejan("aaa1", 30));

	cout << q.front().name << " " << q.front().age << endl;
	cout << q.back().name << " " << q.back().age << endl;
	cout << endl;
	while (!q.empty())
	{
		cout << q.front().name << " " << q.front().age << endl;
		q.pop();
	}

	cout << "size:" << q.size() << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
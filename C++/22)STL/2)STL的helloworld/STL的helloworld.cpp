#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector> // 容器的头文件
#include<algorithm> // 算法头文件
#include<string>
using namespace std;

// 1.存储基础数据类型
void myprint(int val)
{
	cout << val << " ";
}
void test()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	// 获取开始位置的迭代器
	vector<int>::iterator begin = v.begin();
	// 获取结束位置的迭代器
	vector<int>::iterator end = v.end();

	// 遍历算法
	for_each(begin, end, myprint);
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
ostream& operator<<(ostream& out, Dejan& d)
{
	out << "Name:" << d.name << " Age:" << d.age << endl;
	return out;
}
void test02()
{
	vector<Dejan> v;
	v.push_back(Dejan("aaa1", 10));
	v.push_back(Dejan("aaa2", 20));
	v.push_back(Dejan("aaa3", 30));
	v.push_back(Dejan("aaa4", 40));
	v.push_back(Dejan("aaa5", 50));

	vector<Dejan>::iterator begin = v.begin();
	vector<Dejan>::iterator end = v.end();

	while (begin != end)
	{
		cout << (*begin);
		++begin;
	}
}

// 3.存储对象的指针
void test03()
{
	vector<Dejan*> v;
	// 创建数据
	Dejan *p1 = new Dejan("aaa1", 10);
	Dejan *p2 = new Dejan("aaa2", 20);
	Dejan *p3 = new Dejan("aaa3", 30);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);

	vector<Dejan*>::iterator begin = v.begin();
	vector<Dejan*>::iterator end = v.end();

	while (begin != end)
	{
		cout << "Name:" << (*begin)->name << " Age:" << (*begin)->age << endl;
		++begin;
	}
}

// 4.容器嵌套容器
void myforeach(vector<int> v)
{
	vector<int>::iterator begin = v.begin();
	vector<int>::iterator end = v.end();
	while (begin != end)
	{
		cout << *begin << endl;
		++begin;
	}
}
void test04()
{
	vector<vector<int>> vs;
	// 创建数据
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;
	vector<int> v5;

	// 给这些容器数值
	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i + 10);
		v2.push_back(i + 20);
		v3.push_back(i + 30);
		v4.push_back(i + 40);
		v5.push_back(i + 50);
	}

	vs.push_back(v1);
	vs.push_back(v2);
	vs.push_back(v3);
	vs.push_back(v4);
	vs.push_back(v5);

	vector<vector<int>>::iterator begin = vs.begin();
	vector<vector<int>>::iterator end = vs.end();

	while (begin != end)
	{
		vector<int>::iterator s_begin = (*begin).begin();
		vector<int>::iterator s_end = (*begin).end();

		while (s_begin != s_end)
		{
			cout << (*s_begin) << " ";
			++s_begin;
		}
		++begin;
	}
	cout << endl;
	cout << "------------------------------" << endl;

	for_each(vs.begin(), vs.end(), myforeach);
}

int main()
{
	test04();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<functional>
#include<numeric>
#include<vector>
#include<string>
using namespace std;
/*
accumulate算法 计算容器元素累计总和
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value累加值

accumulate(iterator beg, iterator end, value)
*/
void test01()
{
	vector<int> v1;

	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);

	int ret = accumulate(v1.begin(), v1.end(), 1);//第三个参数是在元素累计之后加
	cout << ret << endl;
}

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

struct MyPlus
{
	/*int operator()(int val,Maker &m)
	{
		return val + m.age;

	}*/
	string operator()(string str, Dejan &d)
	{
		return str += d.name;
	}
};

void test02()
{
	vector<Dejan> v;
	v.push_back(Dejan("aaa1", 10));
	v.push_back(Dejan("aaa1", 20));
	v.push_back(Dejan("aaa1", 30));
	/*
	int ret = accumulate(v.begin(), v.end(), 0, MyPlus());
	cout << ret << endl;*/
	string str2 = " ";
	string str = accumulate(v.begin(), v.end(), str2, MyPlus());
	cout << str << endl;
}

/*
fill算法 向容器中添加元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value t填充元素

fill(iterator beg, iterator end, value)


*/
void test03()
{
	vector<int> v;
	v.resize(10);
	fill(v.begin(), v.end(), 100);
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " ";
	}
}

int main()
{
	test03();

	system("pause");
	return 0;
}
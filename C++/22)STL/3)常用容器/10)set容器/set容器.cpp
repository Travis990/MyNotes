#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>
using namespace std;

void test()
{
	set<int>::iterator it;
	it--;
	it++;
	//it + 2; error: 不是随机
	// 双向
	// 数据结构是二叉树
}

void printSet(set<int> &s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01()
{
	set<int> s;
	//默认排序是升序

	s.insert(4);
	s.insert(2);
	s.insert(3);
	s.insert(6);
	s.insert(8);

	printSet(s);
}

struct myfunc
{
	bool operator()(int v1, int v2) const
	{	// apply operator< to operands
		return (v1 > v2);
	}
};

void printSetmyfunc(set<int, myfunc> &s)
{
	for (set<int, myfunc>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test02()
{
	set<int, myfunc> s;

	s.insert(4);
	s.insert(2);
	s.insert(3);
	s.insert(6);
	s.insert(8);

	printSetmyfunc(s);
}

void test03()
{
	set<int, myfunc> s;

	s.insert(4);
	s.insert(2);
	s.insert(3);
	s.insert(6);
	s.insert(8);

	printSetmyfunc(s);

	s.insert(3); //编译不会报错，运行也不会报错，只没有把重复的数据插入

	printSetmyfunc(s);
	pair<set<int, myfunc>::iterator, bool> ret = s.insert(9);
	if (ret.second)
	{
		cout << "插入成功" << endl;
	}
	else
	{
		cout << "插入失败" << endl;
	}
}

/*
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
1.	count(key);//查找键key的元素个数
2.	lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
3.	upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

*/
void test04()
{
	set<int> s;
	s.insert(1);
	s.insert(8);
	s.insert(3);
	s.insert(4);
	s.insert(6);
	s.insert(5);
	set<int>::iterator it = s.find(2);

	if (it == s.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找的值是：" << *it << endl;
	}
	cout << "------------------------" << endl;
	it = s.lower_bound(2);
	if (it == s.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找的值是：" << *it << endl;
	}

	it = s.upper_bound(3);
	if (it == s.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找的值是：" << *it << endl;
	}
	cout << "------------------------" << endl;
	pair<set<int>::iterator, set<int>::iterator> ret = s.equal_range(3);
	cout << *(ret.first) << endl;
	cout << *(ret.second) << endl;
}

// 自定义数据类型
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

struct Dejanfunc
{	// functor for operator<
	bool operator()(const Dejan &d1, const Dejan &d2)
	{	// apply operator< to operands
		return d1.age > d2.age;
	}
};

void test05()
{
	set<Dejan, Dejanfunc> s;
	// 默认排序是升序
	s.insert(Dejan("aaa1", 10));
	s.insert(Dejan("aaa1", 20));
	s.insert(Dejan("aaa1", 30));
	s.insert(Dejan("aaa1", 40));
	s.insert(Dejan("aaa1", 50));

	for (set<Dejan, Dejanfunc>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << "Name:" << it->name << " Age:" << it->age << endl;
	}
}

//	count(key);//查找键key的元素个数
void test06()
{
	multiset<int> ms;
	ms.insert(1);
	ms.insert(2);
	ms.insert(2);
	ms.insert(2);
	ms.insert(1);

	int ret = ms.count(2);
	cout << ret << endl;
}

int main()
{
	test06();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<functional>
#include<numeric>
#include<vector>
using namespace std;
/*
set_intersection算法 求两个set集合的交集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址

set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
*/
//交集
void test01()
{
	vector<int> v1, v2;
	//1 2 3 4 5 6 7 8 
	for (int i = 0; i < 9; i++)
	{
		v1.push_back(i);
	}
	//5 6 7 8 9 10 11 12 13 14
	for (int i = 5; i < 15; i++)
	{
		v2.push_back(i);
	}

	vector<int> v3;
	v3.resize(min(v1.size(), v2.size()));//取2个容器中小的容器的大小

	//返回的是目标容器的最后一个元素的迭代器
	vector<int>::iterator myend = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for (vector<int>::iterator it = v3.begin(); it != myend; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

/*
set_union算法 求两个set集合的并集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址

set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
*/
//并集
void test02()
{
	vector<int> v1, v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	for (int i = 5; i < 15; i++)
	{
		v2.push_back(i);
	}

	vector<int> v3;
	v3.resize(v1.size() + v2.size());

	//返回的是目标容器的最后一个元素的迭代器
	vector<int>::iterator myend = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for (vector<int>::iterator it = v3.begin(); it != myend; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

/*
set_difference算法 求两个set集合的差集
注意:两个集合必须是有序序列
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器
@return 目标容器的最后一个元素的迭代器地址

set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
*/
//差集
//假如集合A 1 2 3 4 5，B集合是2 3 4 5 6，A集合减B集合等于1
//
void test03()
{
	vector<int> v1, v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);

	vector<int> v3;
	v3.resize(v1.size() + v2.size());
	//返回的是目标容器的最后一个元素的迭代器
	vector<int>::iterator myend = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for (vector<int>::iterator it = v3.begin(); it != myend; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main()
{
	test03();

	system("pause");
	return 0;
}
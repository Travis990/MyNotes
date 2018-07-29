#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<map>
#include<string>
using namespace std;

void test()
{
	//数据结构是二叉树
	map<int, int>::iterator it;
	it++;
	it--;
	//it + 2;
	//双向
}

void printMap(map<int, string> &mymap)
{
	for (map<int, string>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
}

void test01()
{
	map<int, string> mymap;

	//1.第一种插入数据
	mymap.insert(pair<int, string>(3, "aaa"));

	//2.第二种插入数据
	mymap.insert(make_pair(6, "ddd"));

	//3.第三种插入数据
	mymap.insert(map<int, string>::value_type(2, "bbb"));

	//4.第四种插入数据
	mymap[4] = "ccc";

	printMap(mymap);

	cout << mymap.size() << endl;
	mymap[4] = "666";
	cout << mymap[4] << endl;

	cout << mymap.size() << endl;

	//map容器是以键值为主，必须要有键值
}

/*
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

*/
void test02()
{
	map<int, string> mymap;
	mymap[1] = "aaa1";
	mymap[2] = "aaa2";
	mymap[3] = "aaa3";
	mymap[4] = "aaa4";
	mymap[5] = "aaa5";
	map<int, string>::iterator it = mymap.find(30);
	if (it == mymap.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功" << endl;
		cout << it->first << " " << it->second << endl;
	}

	multimap<int, string> mumap;
	mumap.insert(make_pair(1, "aa"));
	mumap.insert(make_pair(2, "aa"));
	mumap.insert(make_pair(2, "aa"));
	mumap.insert(make_pair(2, "aa"));
	mumap.insert(make_pair(1, "aa"));

	cout << mumap.count(2) << endl;

	it = mymap.lower_bound(8);
	if (it == mymap.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功" << endl;
		cout << it->first << " " << it->second << endl;
	}

	it = mymap.upper_bound(3);
	if (it == mymap.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功" << endl;
		cout << it->first << " " << it->second << endl;
	}
	cout << "-------------------" << endl;
	//返回两个元素的迭代器，元素的对组
	pair<map<int, string>::iterator, map<int, string>::iterator> ret = mymap.equal_range(3);
	if (ret.first != mymap.end())
	{
		cout << "key:" << ret.first->first << " value:" << ret.first->second << endl;
	}
	if (ret.second != mymap.end())
	{
		cout << "key:" << ret.second->first << " value:" << ret.second->second << endl;
	}
}

int main()
{
	test02();

	system("pause");
	return 0;
}
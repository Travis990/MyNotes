#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
using namespace std;

void test()
{
	list<int> mylist;

	for (int i = 0; i < 10; i++)
	{
		mylist.push_back(i);
	}

	// 证明是循环的  vs 2015 2017   _Myhead()
	list<int>::_Nodeptr node = mylist._Myhead()->_Next;//获取头节点的下一个节点
	for (int i = 0; i < mylist._Mysize() * 2; i++) // 2015 2017 _Mysize()
	{
		cout << "node:" << node->_Myval << endl; // 获取数据
		node = node->_Next;
		// 跳过头节点
		if (node == mylist._Myhead())
		{
			node = node->_Next;
		}
	}

	// 证明是双向
	list<int>::iterator it;
	it++;
	it--;

	//it + 2; error: 不是随机
}


int main()
{
	test();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
using namespace std;

void printlist(const list<int> &mylist)
{
	for (list<int>::const_iterator it = mylist.begin(); it != mylist.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

/*
list<T> lstT;//list采用采用模板类实现,对象的默认构造形式：
list(beg,end);//构造函数将[beg, end)区间中的元素拷贝给本身。
list(n,elem);//构造函数将n个elem拷贝给本身。
list(const list &lst);//拷贝构造函数。

*/
void test01()
{
	list<int> mylist(10, 6);

	list<int> mylist2(mylist.begin(), mylist.end());

	printlist(mylist);
	printlist(mylist2);
	cout << "--------------" << endl;

	//list迭代器不是随机
	//sort他需要随机迭代器才能使用，不能使用算法中的排序，list容器自己提供排序函数
	list<int> mylist3;
	for (int i = 0; i < 10; i++)
	{
		mylist3.push_back(i + 1);
	}
	mylist3.push_back(2);
	mylist3.push_back(11);
	mylist3.push_back(8);

	printlist(mylist3);

	mylist3.sort();

	printlist(mylist3);
}

/*
push_back(elem);//在容器尾部加入一个元素
pop_back();//删除容器中最后一个元素
push_front(elem);//在容器开头插入一个元素
pop_front();//从容器开头移除第一个元素
insert(pos,elem);//在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
remove(elem);//删除容器中所有与elem值匹配的元素。

*/
bool mycompare(int val)
{
	return val > 300;
}

struct _mycompare
{
	bool operator()(int val)
	{
		return val > 300;
	}
};

void test02()
{
	list<int> mylist;

	mylist.push_back(10);
	mylist.push_back(20);
	mylist.push_back(30);
	mylist.push_back(40);
	mylist.push_front(100);
	mylist.push_front(200);
	mylist.push_front(300);
	mylist.push_front(400);

	printlist(mylist);

	vector<int> v;
	v.push_back(1000);
	v.push_back(2000);
	v.push_back(3000);

	mylist.insert(mylist.begin(), v.begin(), v.end());
	printlist(mylist);

	mylist.remove(300);

	printlist(mylist);

	//mylist.remove_if(mycompare);  // 全局函数
	mylist.remove_if(_mycompare()); // 谓词
	printlist(mylist);
	cout << mylist.size() << endl;
}

void test03()
{
	list<int> mylist;

	mylist.assign(8, 10);

	printlist(mylist);

	cout << mylist.front() << endl;
	cout << mylist.back() << endl;
}

// 反转
bool func(int v1, int v2)
{
	return v1 > v2;
}
struct _DESC
{
	bool operator()(int v1, int v2)
	{
		return v1 > v2;
	}
};

void test04()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(3);
	mylist.push_back(5);

	printlist(mylist);

	mylist.reverse();
	printlist(mylist);

	mylist.sort(); // 默认排序是升序
	printlist(mylist);

	//mylist.sort(func); // 普通函数
	mylist.sort(_DESC()); // 谓词
	printlist(mylist);
}


int main()
{
	test04();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

void test()
{
	vector<int>::iterator it;
	it--;
	it++;
	it + 2;
	//连续的存储空间，
	//双向，随机
}

/*
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

*/

void printVector(const vector<int> &vec)
{
	for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	int arr[] = { 2, 4, 1, 3, 9 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(int));

	printVector(v);

	vector<int> v2(10, 6);
	printVector(v2);
}

/*
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector&operator=(const vector  &vec);//重载等号操作符
swap(vec);// 将vec与本身的元素互换。

*/
void test02()
{
	vector<int> v;
	v.assign(10, 6);

	vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(30);

	printVector(v);
	printVector(v2);

	cout << "----------------" << endl;

	v.swap(v2); // 交换指针

	printVector(v);
	printVector(v2);
}

/*
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的容量
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。

*/
void test03()
{
	vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);
	v2.push_back(30);

	cout << "v2.size:" << v2.size() << endl;

	v2.resize(5); // 开辟空间，给默认值，默认值是0
	cout << "v2.size:" << v2.size() << endl;
	printVector(v2);

	v2.reserve(20);
	v2.push_back(100);

	printVector(v2);
	cout << "v2.size:" << v2.size() << endl;
	cout << v2.capacity() << endl;

	//cout << v2[10] << endl;  error
}

// 预留空间
void test04()
{
	vector<int> v;

	v.resize(5); // 5个int的空间，默认赋值0，

	v.push_back(10);
	cout << "v.capacity() =" << v.capacity() << endl;
	cout << "v.size()=" << v.size() << endl;

	cout << "-----------------" << endl;

	vector<int> v2;

	v2.reserve(5); // 不初始化
	v2.push_back(10);
	cout << "v2.capacity() =" << v2.capacity() << endl;
	cout << "v2.size()=" << v2.size() << endl;
}

void test05()
{
	vector<int> v;

	v.reserve(1000000);

	int *p = NULL;
	int num = 0;
	for (int i = 0; i < 1000000; i++)
	{
		v.push_back(i);
		// 判断申请空间的次数
		if (p != &v[0]) // 如果p不等于首地址，那么证明申请了新空间
		{
			p = &v[0];
			num++;
		}
	}

	cout << "num=" << num << endl;
}

/*
at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
operator[];//返回索引idx所指的数据，越界时，运行直接报错
front();//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素

*/
void test06()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	cout << v.front() << endl;
	cout << v.back() << endl;

	v.front() = 100;
	v.back() = 200;

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

/*
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele.
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素

*/
void test07()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	v.insert(v.begin() + 2, 100);
	printVector(v);

	v.pop_back();
	printVector(v);

	v.erase(v.begin());
	printVector(v);

	v.erase(v.begin(), v.end());
	printVector(v);
}

int main()
{
	test07();

	system("pause");
	return 0;
}
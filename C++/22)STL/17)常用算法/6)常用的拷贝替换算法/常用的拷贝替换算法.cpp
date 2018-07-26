#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;

/*
copy算法 将容器内指定范围的元素拷贝到另一容器中
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param dest 目标容器结束迭代器

copy(iterator beg, iterator end, iterator dest)
*/
void test01()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);

	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	for_each(v2.begin(), v2.end(), [](int val) {cout << val << " "; });
	cout << endl;
}

/*
//质变算法
replace算法 将容器内指定范围的旧元素修改为新元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param oldvalue 旧元素
@param oldvalue 新元素

replace(iterator beg, iterator end, oldvalue, newvalue)
*/

void test02()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	replace(v1.begin(), v1.end(), 20, 200);
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
	cout << endl;
}

/*
swap算法 互换两个容器的元素
@param c1容器1
@param c2容器2

swap(container c1, container c2)
*/
void test03()
{
	vector<int> v1;
	vector<int> v2;

	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i + 1);
		v2.push_back(i + 10);
	}
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
	cout << endl;
	for_each(v2.begin(), v2.end(), [](int val) {cout << val << " "; });
	cout << endl;
	cout << "交换之后:" << endl;
	swap(v1, v2);

	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
	cout << endl;
	for_each(v2.begin(), v2.end(), [](int val) {cout << val << " "; });
	cout << endl;
}

int main()
{
	test03();

	system("pause");
	return 0;
}
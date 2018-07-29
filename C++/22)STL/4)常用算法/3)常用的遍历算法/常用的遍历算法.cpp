#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
transform算法 将指定容器区间元素搬运到另一容器中
注意 : transform 不会给目标容器分配内存，所以需要我们提前分配好内存
@param beg1 源容器开始迭代器
@param end1 源容器结束迭代器
@param beg2 目标容器开始迭代器
@param _cakkback 回调函数或者函数对象
@return 返回目标容器迭代器

transform(iterator beg1, iterator end1, iterator beg2, _callbakc)
*/
struct Myadd
{
	int operator()(int v1)
	{
		return v1 + 100;
	}
};
void test01()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	vector<int> v2;
	//开辟空间
	v2.resize(v.size());//会初始化
	transform(v.begin(), v.end(), v2.begin(), Myadd());

	for_each(v2.begin(), v2.end(), [](int val) {cout << val << " "; });
}

//把两个容器中的元素经过处理搬运到第三个容器中
//注意：两个容器中的元素个数需要相同
struct Myadd2
{
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

void test02()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	vector<int> v2;
	v2.push_back(100);
	v2.push_back(200);
	v2.push_back(300);
	v2.push_back(400);
	v2.push_back(500);

	vector<int> v3;
	v3.resize(v.size());

	transform(v.begin(), v.end(), v2.begin(), v3.begin(), Myadd2());
	for_each(v3.begin(), v3.end(), [](int val)->void {cout << val << " "; });
}

int main()
{
	test02();

	system("pause");
	return 0;
}
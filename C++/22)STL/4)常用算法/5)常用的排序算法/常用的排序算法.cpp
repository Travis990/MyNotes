#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<ctime>
using namespace std;
/*
merge算法 容器元素合并，并存储到另一容器中
@param beg1 容器1开始迭代器
@param end1 容器1结束迭代器
@param beg2 容器2开始迭代器
@param end2 容器2结束迭代器
@param dest  目标容器开始迭代器

merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
*/
void test01()
{
	vector<int> v1;
	vector<int> v2;

	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i + 1);
		v2.push_back(i + 5);
	}

	vector<int> v3;
	v3.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for_each(v3.begin(), v3.end(), [](int val) {cout << val << " "; });
	cout << "-----------------" << endl;
	//如果要改变排序，那么数据要降序才能使用greater<int>()
	vector<int> v11;
	vector<int> v22;

	for (int i = 10; i > 0; i--)
	{
		v11.push_back(i);
		v22.push_back(i);
	}

	vector<int> v33;
	v33.resize(v11.size() + v22.size());
	merge(v11.begin(), v11.end(), v22.begin(), v22.end(), v33.begin(), greater<int>());
	for_each(v33.begin(), v33.end(), [](int val) {cout << val << " "; });
}

/*
洗牌
sort算法 对指定范围内的元素随机调整次序
@param beg 容器开始迭代器
@param end 容器结束迭代器

random_shuffle(iterator beg, iterator end)
*/
void test02()
{
	vector<int> v1;
	for (int i = 5; i > 0; i--)
	{
		v1.push_back(i + 1);
	}
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
	cout << "--------------------" << endl;

	//引入随机种子
	srand((unsigned int)time(NULL));
	random_shuffle(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
}

/*
reverse算法 反转指定范围的元素
@param beg 容器开始迭代器
@param end 容器结束迭代器

reverse(iterator beg, iterator end)
*/
void test03()
{
	vector<int> v1;
	for (int i = 5; i > 0; i--)
	{
		v1.push_back(i + 1);
	}
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
	cout << "--------------------" << endl;

	reverse(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), [](int val) {cout << val << " "; });
}

int main()
{
	test03();

	system("pause");
	return 0;
}
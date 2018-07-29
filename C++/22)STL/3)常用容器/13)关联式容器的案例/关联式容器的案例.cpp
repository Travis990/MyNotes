#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<ctime>
using namespace std;

//公司今天招聘了5个员工，5名员工进入公司之后，需要指派员工在那个部门工作
//人员信息有: 姓名 年龄 电话 工资等组成
//通过Multimap进行信息的插入 保存 显示
//分部门显示员工信息 显示全部员工信息

#define SALE_DEPATMENT 1 //销售部门
#define DEVELOP_DEPATMENT 2 //研发部门
#define FINACIAL_DEPATMENT 3 //财务部门

//抽象员工
class Woker
{
public:
	string name;
	int age;
	int mSalary;
};

//创建员工
void CreateWoker(vector<Woker> &vWoker)
{
	srand((unsigned int)time(NULL));
	string setName = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		Woker woker;
		woker.name = "员工";
		woker.name += setName[i];
		woker.age = rand() % 20 + 20;
		woker.mSalary = rand() % 10000 + 10000;
		vWoker.push_back(woker);
	}
}

//员工分组
void WokerByGroup(vector<Woker> &vWoker, multimap<int, Woker> &mWoker)
{
	// 遍历员工
	for (vector<Woker>::iterator it = vWoker.begin(); it != vWoker.end(); ++it)
	{
		int dexid = rand() % 3 + 1;
		// 员工分组
		mWoker.insert(make_pair(dexid, *it));
	}
}

void myGroup(multimap<int, Woker> &mWoker, int depId)
{
	/*
	1 2
	2 1
	3 2
	*/
	/*
	key value
	1    ....
	1    .....
	2    .....
	3    .....
	3    .....
	*/
	//查找部门中有多少个人
	multimap<int, Woker>::iterator it = mWoker.find(depId);
	int mcount = mWoker.count(depId);
	int index = 0;
	for (; it != mWoker.end() && index < mcount; ++it, ++index)
	{
		cout << "Name:" << it->second.name << " Age:" << it->second.age << " Salary:" << it->second.mSalary << endl;
	}
}

// 打印各组的员工信息
void printWoker(multimap<int, Woker> &mWoker)
{
	cout << "销售部门员工信息如下:" << endl;
	myGroup(mWoker, SALE_DEPATMENT);

	cout << "研发部门员工信息如下:" << endl;
	myGroup(mWoker, DEVELOP_DEPATMENT);

	cout << "财务部门员工信息如下:" << endl;
	myGroup(mWoker, FINACIAL_DEPATMENT);
}

void test()
{
	vector<Woker> vWoker; // 保存未分组的员工信息
	multimap<int, Woker> mWoker; // 保存分组后的员工信息

	// 创建员工
	CreateWoker(vWoker);

	// 分组
	WokerByGroup(vWoker, mWoker);

	// 打印
	printWoker(mWoker);
}

int main()
{
	test();

	system("pause");
	return 0;
}
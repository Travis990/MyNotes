#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>
using namespace std;

/*struct Myfunc
{
	void operator()(int val)
	{
		cout << val << " " << endl;
	}
};*/

//函数对象适配
//打印出来的数据都加上10
//适配函数对象的步骤:
//1.继承binary_function
//2.要把参数变为2个
//3.要把重载函数变为常函数
struct Myfunc
	:public binary_function<int, int, void>
{
	void operator()(const int v1, const int v2) const
	{
		cout << v1 + v2 << " " << endl;
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

	//for_each(v.begin(),v.end(), Myfunc());

	//4.绑定适配器
	//bind2nd 
	for_each(v.begin(), v.end(), bind2nd(Myfunc(), 10));
}

//普通函数适配
//1.把全局函数的参数变为2个
void Myprint(int v1, int v2)
{
	cout << v1 + v2 << " " << endl;
}

void test02()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	//for_each(v.begin(), v.end(), Myprint);

	//2.把普通函数变为函数对象
	//ptr_fun
	//3.绑定适配器
	for_each(v.begin(), v.end(), bind2nd(ptr_fun(Myprint), 10));
}

//成员函数适配
//mem_fun适应对象指针  mem_fun_ref适应对象
class Dejan
{
public:
	Dejan(string name, int age)
	{
		this->name = name;
		this->age = age;
	}

	void PrintDejan()
	{
		cout << "成员函数打印:" << this->name << " " << this->age << endl;
	}
public:
	string name;
	int age;
};

void test03()
{
	vector<Dejan> v;
	v.push_back(Dejan("aaa1", 10));
	v.push_back(Dejan("aaa1", 20));
	v.push_back(Dejan("aaa1", 30));
	v.push_back(Dejan("aaa1", 40));
	v.push_back(Dejan("aaa1", 50));

	for_each(v.begin(), v.end(), mem_fun_ref(&Dejan::PrintDejan));
	cout << "---------------------------" << endl;

	vector<Dejan*> vp;
	vp.push_back(new Dejan("bbb1", 10));
	vp.push_back(new Dejan("bbb2", 20));
	vp.push_back(new Dejan("bbb3", 30));
	vp.push_back(new Dejan("bbb4", 40));
	vp.push_back(new Dejan("bbb5", 50));
	for_each(vp.begin(), vp.end(), mem_fun(&Dejan::PrintDejan));
}

//取反适配not1(一元函数对象取反) not2(二元函数对象取反)
//1.继承unary_function
//2.把重载函数变为常函数
struct Myfunc2
	:public unary_function<int, bool>
{
	bool operator()(int val) const
	{
		return val >= 40;
	}
};
void test04()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	//find_if()
	//3.绑定适配器
	vector<int>::iterator it = find_if(v.begin(), v.end(), not1(Myfunc2()));
	if (it == v.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功" << *it << endl;//10
	}
}

int main()
{
	test04();

	system("pause");
	return 0;
}
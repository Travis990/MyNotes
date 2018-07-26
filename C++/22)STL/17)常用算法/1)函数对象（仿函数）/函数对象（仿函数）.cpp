#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//如果要计算函数被调用的次数
int a = 0;//我们要避免使用全局变量，多线程，全局变量会变为竞争资源
void func()
{
	a++;
	cout << a << endl;
}
//仿函数也叫函数对象
struct Myfunc {
public:
	Myfunc()
	{
		age = 0;
	}
	void operator()()
	{
		cout << "hello" << endl;
		age++;
	}
public:
	int age;
};

//1.如果使用函数对象，就不用使用全局变量
//2.类里面的函数都默认成为内联函数
//3.全局函数一般不会成为内联函数，进行了取地址操作，就不会成为内联函数

void test01()
{
	Myfunc func;
	for (int i = 0; i < 10; i++)
	{
		//func(); // 全局函数
		func(); // 函数对象
	}
	cout << func.age << endl;

}

//内建的函数对象
//函数对象不是函数，是对象
void test02()
{
	plus<int> myplus;
	cout << myplus(10, 20) << endl;

	vector<int> v;
	v.push_back(2);
	v.push_back(1);
	v.push_back(9);
	v.push_back(6);
	v.push_back(3);
	//函数对象后面要加(),函数不需要
	sort(v.begin(), v.end(),greater<int>());//默认升序，需要改为降序

	for_each(v.begin(), v.end(), [](int val) {cout << val << " "; });
}

int main()
{
	test02();

	system("pause");
	return 0;
}
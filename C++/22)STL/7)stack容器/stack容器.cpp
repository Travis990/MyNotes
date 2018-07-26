#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<string>
using namespace std;

/*
stack<T> stkT;//stack采用模板类实现， stack对象的默认构造形式：
stack(const stack &stk);//拷贝构造函数

*/
//先进后出

//1.放基础数据类型
void test01()
{
	stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);
	s.push(50);

	while (!s.empty())
	{
		// 输出栈顶元素
		cout << s.top() << endl;
		// 弹出栈顶元素
		s.pop();
	}

	cout << "size:" << s.size() << endl;
}

// 2.存储对象
class Dejan
{
public:
	Dejan(string name, int age)
	{
		this->name = name;
		this->age = age;
	}
public:
	string name;
	int age;
};

void test02()
{
	stack<Dejan> s;
	s.push(Dejan("aaa1", 10));
	s.push(Dejan("aaa2", 20));
	s.push(Dejan("aaa3", 30));
	while (!s.empty())
	{
		// 输出栈顶元素
		cout << s.top().name << " " << s.top().age << endl;
		// 弹出栈顶元素
		s.pop();
	}

	cout << "size:" << s.size() << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
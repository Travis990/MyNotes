#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// new 用于数组,基础数据类型
void test01()
{
	// 从堆区申请空间
	int *arr = new int[10];
	// malloc(sizeof(int)* 10);
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

	double *arrd = new double[10];

	// new的时候有中括号，那么delete时必须也要有[]
	delete[] arr;
	delete[] arrd;
}

// 类,自定义数据类型
class Dejan
{
public:
	Dejan()
	{
		cout << "无参构造" << endl;
	}
	Dejan(int a)
	{
		cout << "有参构造" << endl;
	}
	~Dejan()
	{
		cout << "析构函数" << endl;
	}
};

// 对象数组
void test02()
{
	Dejan *p = new Dejan[2]; // 从堆区申请2个对象大小的空间
	delete[] p;

	// Dejan *q = new Dejan[2]{Dejan(10),Dejan(20)}; 大部分编译器不支持
}

int main()
{
	test02();

	system("pause");
	return 0;
}
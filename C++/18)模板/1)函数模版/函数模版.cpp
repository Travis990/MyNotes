#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void mySwapInt(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void mySwapDouble(double &a, double &b)
{
	double tmp = a;
	a = b;
	b = tmp;
}

void test()
{
	int a = 10;
	int b = 20;

	double a1 = 10.10;
	double b1 = 20.20;
	mySwapInt(a, b);
	mySwapDouble(a1, b1);
}

// 告诉编译器紧跟着的函数中有T，你不要报错
template<class T> // T是虚拟的数据类型，不一定是T，T1 T2 M
void mySwap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
void func(T &a)
{

}

void test2()
{
	int a = 10;
	int b = 20;

	double a1 = 10.10;
	double b1 = 20.20;
	// 编译器会自动推导数据类型
	mySwap(a, b);
	/*在函数调用时会产生模版函数
	void mySwap(int &a,int &b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	*/
	mySwap(a1, b1);
	/*
	void mySwap(double &a,double &b)
	{
		double tmp = a;
		a = b;
		b = tmp;
	}
	*/
	// 编译器会对函数模版和类模版进行二次编译
	cout << "a=" << a << " b=" << b << endl;
	cout << "a1=" << a1 << " b1" << b1 << endl;

	int a2 = 10;
	char c = 'a';
	// 传入的参数类型必须一致
	// mySwap(a2, c); error

	mySwap<int>(a, b); // <int>参数列表
	//mySwap<int>(a1, b1);//显示的告诉编译器传入什么数据类型，就必须传入什么数据类型

	//mySwap<double>();  error
	//mySwap();err

	//用函数模版实现对char和int类型的数据进行排序(选择排序，从大到小)，打印
}

template<class T>
void mySort(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int max = i; // 定义最大数据的下标
		for (int j = i + 1; j < len; j++)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}
		if (max != i)
		{
			// 进行交换
			mySwap(arr[max], arr[i]);
		}
	}
}

template<class T>
void myPrint(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void test03()
{
	char str[] = "hello";
	int len = sizeof(str) / sizeof(char);
	myPrint(str, len);
	mySort(str, len);
	myPrint(str, len);
	cout << "---------------------------" << endl;
	int arr[] = { 3,7,2,1 };
	len = sizeof(arr) / sizeof(int);
	myPrint(arr, len);
	mySort(arr, len);
	myPrint(arr, len);
}

// 编译器会对函数模版和类模版进行二次编译
template<class T1, class T2>
int func(T1 a, T2 b)
{
	return a + b;
}

void test04()
{
	//func(20, "aaa");
	/*
	int func(int a, const char* b)
	{
		return a + b;
	}
	*/
}

int main()
{
	test04();

	system("pause");
	return 0;
}
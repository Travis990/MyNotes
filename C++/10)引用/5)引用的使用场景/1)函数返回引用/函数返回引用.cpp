#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int& func(int &a,int &b)
{
	int sum = a + b;
	return sum;
}
// 1.不要返回局部变量的引用
int& func2()
{
	int sum = 100;
	return sum;
}
int& func3()
{
	static int sum = 100;
	return sum;
}
void test()
{
	int a = 10;
	int b = 20;
	int ret = func(a,b);
	cout << "ret=" << ret << endl; // 30

	func2() = 200;
	cout << "func2()=" << func2() << endl; // 100
	func3() = 300;
	cout << "func3()=" << func3() << endl; // 300
}

int func4()
{
	int a = 10;
	return a;
}

// 如果要函数当左值，函数返回必须是引用
int& func5()
{
	static int a = 20;
	return a;
}
void test2()
{
	//func4() = 200; error:非左值
	//10 = 200;
	// 如果函数返回的引用，那么函数可以当左值又可以当右值
	func5() = 200;
	int ret = func5();
	cout << "func5()=" << ret << endl;
}


int main()
{
	test2();

	system("pause");
	return 0;
}
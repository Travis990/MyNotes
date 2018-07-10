#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
// 宏函数
#define ADD(x,y) x+y

// 加上inline表示向编译器申请成为内联函数
// 能不能成为内联函数，看编译器
// 内联函数：内联函数具有宏函数的效率，类中的成员函数自动申请为内联函数，能不能成为内联函数要看编译器
inline int add(int x, int y)
{
	return x + y;
}

void test()
{
	// 314 + 343 * 2
	int ret1 = ADD(314, 343) * 2; // 1314
	cout << "ret1=" << ret1 << endl; // 1000
	int ret2 = add(314, 343) * 2;
	cout << "ret2=" << ret2 << endl;
}

#define COMPARE(x,y) ((x) < (y) ? (x) : (y))
inline int Compare(int x, int y) {
	return x < y ? x : y;
}
void test02()
{
	int a = 1;
	int b = 3;
	//              COMPARE(++a,b)==((++a)<(b)?++a:b)     //这里++两次
	//cout << "COMPARE(++a, b):" << COMPARE(++a, b) << endl; // 3
	cout << "Compare(int x,int y):" << Compare(++a, b) << endl; //2
}

int main()
{
	test02();

	system("pause");
	return 0;
}
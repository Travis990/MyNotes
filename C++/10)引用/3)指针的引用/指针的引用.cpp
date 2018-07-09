#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//指针的引用
void func(char **tmp)
{
	char *p = (char*)malloc(50);
	memset(p, 0, 50);
	strcpy(p, "hello");
	*tmp = p;
}
void test()
{
	char *p = NULL;
	func(&p);
	cout << p << endl;
}

void func2(char* &tmp)
{
	tmp = (char*)malloc(50);
	memset(tmp, 0, 50);
	strcpy(tmp, "world");
}
void test2()
{
	char* p = NULL;
	func2(p);
	cout << p << endl;
}

int main()
{
	test();
	test2();

	system("pause");
	return 0;
}
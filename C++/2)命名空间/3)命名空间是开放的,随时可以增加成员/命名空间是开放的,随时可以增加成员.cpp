#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace A
{
	int a;
	int b;
	int c = 10;
}

//注意3：命名空间是开放的，随时可以增加成员
namespace A
{
	int d = 20;
}


int main()
{
	cout << "A::c = " << A::c << endl;
	cout << "A::d = " << A::d << endl;

	system("pause");
	return 0;
}
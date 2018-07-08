#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//命名空间是让多人的方法和属性不会重名
//定义命名空间，namespace关键字
namespace A
{
	void test()
	{
		cout << "A" << endl;
	}
	int b = 30;
}

//命名空间的注意:
//注意1：命名空间只能定义在全局
void test() 
{
	/*namespace B{
	        error !
	}*/
}

int main()
{
	A::test();
	cout << A::b << endl;

	system("pause");
	return 0;
}
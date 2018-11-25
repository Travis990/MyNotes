#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyClass
{
public:
	void init(int & intval)
	{
		cout << "use & print" << endl;
	};
	void init(int &&intval)
	{
		cout << "use && print" << endl;
	}
};

int main()
{
	int ae = 10;
	MyClass().init(10);   // use && print
	MyClass().init(ae);   // use & print

	/*
		右值引用是用来支持转移语义的。转移语义可以将资源 ( 堆，系统对象等 )
		从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，
		能够大幅度提高 C++ 应用程序的性能。比如:临时对象的维护 ( 创建和销毁 ) 对性能是有有所消耗的。
	*/

	system("pause");
	return 0;
}
#include "Myarr.h"

void printMyarr(Myarr &arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr.getPosByVal(i) << " ";
	}
	cout << endl;
}

void test()
{
	// 1.分配空间，2.调用构造函数
	Myarr myarr(20, 1);
	printMyarr(myarr);

	for (int i = 0; i < myarr.getSize(); i++)
	{
		myarr.getPosByVal(i) = 100 + i;
	}
	printMyarr(myarr);

	// 头删除, 尾删除
	myarr.PopFront();
	myarr.PopBack();
	printMyarr(myarr);

	// 头插, 尾插
	myarr.PushFront(2);
	myarr.PushBack(10);
	printMyarr(myarr);

	// 指定位置插入元素
	myarr.PopFront();
	myarr.PopBack();

	myarr.InserArr(3, 666);
	printMyarr(myarr);

	// 指定位置修改元素
	myarr.setPosByVal(2, 888);
	printMyarr(myarr);
	cout << "------------------------" << endl;
	Myarr myarr2(myarr);
	printMyarr(myarr2);
}

int main()
{
	test();

	system("pause");
	return 0;
}
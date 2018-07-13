#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Printer
{
public:
	static Printer* getObj()
	{
		return p;
	}

	void PrinterPrint(string name)
	{
		count++;
		cout << name << "打印" << endl;
	}
	int getcount()
	{
		return count;
	}
private:
	Printer()
	{
		count = 0;
	}
	Printer(const Printer &p) {}
private:
	static Printer* p;
	int count; // 计算打印次数
};
Printer* Printer::p = new Printer;

void test()
{
	Printer *p1 = Printer::getObj();
	p1->PrinterPrint("技术部");
	Printer *p2 = Printer::getObj();
	p1->PrinterPrint("销售部");
	Printer *p3 = Printer::getObj();
	p1->PrinterPrint("行政部");
	Printer *p4 = Printer::getObj();
	cout << "count:" << p4->getcount() << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
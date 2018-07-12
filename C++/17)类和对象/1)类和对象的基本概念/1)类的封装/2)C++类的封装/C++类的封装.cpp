#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 封装：1.把变量（属性）和函数（方法）封装在一起
// 2.给这些数据赋予权限

// 类
// 自定义数据类型
class Dejan
{ // 类内
public:
	// 类的默认访问权限是私有
	void func()
	{
		illness;
		mFace;
		son;
	}
public: // 公有, 谁都可以访问
	int mFace;
private: // 私有, 只有你自己可以访问
	int illness;
protected: // 保护, 只有你的子类可以访问
	int son;
};

class Son :public Dejan
{
	void func()
	{
		mFace; // 共有
		// illness;
		son; // 保护
	}
};

//总结：
/*
1.公有权限的数据谁都可以访问
2.私有权限只能自己访问
3.保护权限子类的类内可以访问
4.类内是没有权限之分
*/

// 封装电脑，三个属性，二个方法，提供打印属性的方法
class MyPc
{
public:
	int cpu;
	int size;
	int RAM;
public:
	void SetCpu(int Cpu)
	{
		cpu = Cpu;
	}
	void SetSize(int Size)
	{
		size = Size;
	}
	void SetRAM(int ram)
	{
		RAM = ram;
	}
	void PrintPc()
	{
		cout << cpu << " " << size << " " << RAM << endl;
	}
};

int main()
{
	Dejan dejan;
	dejan.func();
	dejan.mFace;
	cout << "-------------------------" << endl;
	MyPc pc;
	pc.SetCpu(16);
	pc.SetRAM(32);
	pc.SetSize(15);

	pc.PrintPc();

	system("pause");
	return 0;
}
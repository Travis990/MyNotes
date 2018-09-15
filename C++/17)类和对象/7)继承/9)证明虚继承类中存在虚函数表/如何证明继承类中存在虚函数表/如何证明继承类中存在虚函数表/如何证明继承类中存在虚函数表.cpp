#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// 虚基类
class Animal
{
public:
	Animal()
	{
		age = 80;
	}
public:
	int age;
};

// 虚继承
class Sheep :virtual public Animal
{
	// int age
};

class Camel :virtual public Animal
{
	// int age
};

class SheepCamel :public Sheep, public Camel
{
	//int age  --Sheep
	//int age --Camel
};


// 证明"虚继承"类中虚函数表是一个指针
void test()
{
	SheepCamel sp;
	cout << *((int*)(*((int*)&sp + 1)) + 1) << endl;
}

int main()
{
	// class a {}; 一个空类的大小是1字节

	test();
	/* 通过cl命令查看继承中的对象模型  项目配置属性 >> C/C++ >> 命令行 "/d1 reportSingleClassLayoutSheepCamel"
	1>  class SheepCamel	size(12):
	1>  	+---
	1>   0	| +--- (base class Sheep)
	1>   0	| | {vbptr}
	1>  	| +---
	1>   4	| +--- (base class Camel)
	1>   4	| | {vbptr}
	1>  	| +---
	1>  	+---
	1>  	+--- (virtual base Animal)
	1>   8	| age
	1>  	+---
	1>
	1>  SheepCamel::$vbtable@Sheep@:
	1>   0	| 0
	1>   1	| 8 (SheepCameld(Sheep+0)Animal)
	1>
	1>  SheepCamel::$vbtable@Camel@:
	1>   0	| 0
	1>   1	| 4 (SheepCameld(Camel+0)Animal)
	1>  vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
	1>            Animal       8       0       4 0
	*/

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	// 虚函数 告诉编译器，这个函数慢点绑定
	virtual void speak() // 0x001
	{
		cout << "Animal speak()" << endl;
	}
};

class Dog :public Animal
{
public:
	void speak()
	{
		cout << "Dog speak()" << endl;
	}
};

void func(Animal *animal)
{
	animal->speak(); // 0x001
}

//1.func的形参和实参不一致，为什么没有报错
//没报错的条件：1.有继承关系。2.因为步长变小了，寻址范围还是在合法的内存空间
//2.传入的是dog的地址，但打印的是Animal的函数（是因为静态联编）

//静态联编是在编译阶段，编译器就确定了函数的调用地址
//动态联编，让函数变为虚函数，就是告诉编译器晚绑定函数的调用地址

void test()
{
	Dog *dog = new Dog;

	func(dog);
}

int main()
{
	test();

	system("pause");
	return 0;
}
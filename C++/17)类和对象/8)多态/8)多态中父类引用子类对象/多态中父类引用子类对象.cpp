#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void func()
	{

	}
};

class Dog :public Animal
{
public:
	virtual void func()
	{
		cout << "Dog void func()" << endl;
	}
};

void test()
{
	Animal *animal = new Dog; // ¶Ñ
	animal->func();

	Animal &animal2 = Dog(); // Õ»
	animal2.func();

	Animal *a = new Dog;
	Animal* &p = a;

	p->func();
}

int main()
{
	test();

	system("pause");
	return 0;
}
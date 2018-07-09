#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
/*  1.const 修饰的变量有时有空间, 有时没有空间   */
const int a = 10;
const int aa = 20;

// 1) 这种情况, a 就没有空间
void test()
{
	//cout << a << endl;  编译器优化成直接打印10  常量折叠
	cout << a << endl;

	//int *p = &a;   error: 因为aa没有空间,所有取地址错误
}

// 2) const全局变量 - 是不可以间接修改的和C语言中一样。因为 aa 是在全局静态常量区
void test01()
{
	// int *p = &aa;  error: 因为aa没有空间,所有取地址错误

	const int *p = &aa; // 加const后不报错
	//*p = 200;   error: 不能间接修改
}

// 3) volatile 关键字
void test02()
{
	// volatile 禁止编译器优化
	volatile const int a = 10; // 栈
	int *p = (int*)&a; // 如果发生常量折叠，但是对变量取地址了，那么这个变量是有空间

	*p = 100;
	cout << "a = " << a << endl; // 10  cout << "a = " << 10 << endl;  发生了常量折叠
	cout << "*p = " << *p << endl; // 100

	printf("a的地址: %p\n", &a);
	printf("p指向地址: %p\n", p);
}

// 4) 编译器有时候并没有我们想象中那么睿智!
void test03() 
{
	int a = 10;
	const int b = a; // 编译器在编译阶段是不知道变量的值得
	int *p = (int*)&b;
	*p = 100;
	cout << "b=" << b << endl;
	cout << "*p=" << *p << endl;
}

// 5) 编译器不能优化自定义数据类型定义的变量
struct Dejan
{
	int age;
	Dejan() // 构造函数
	{
		age = 18;
	}
};
void test04()
{
	const Dejan dj;
	cout << "age=" << dj.age << endl;

	Dejan *p = (Dejan*)&dj;
	p->age = 28;
	cout << "jd.age=" << dj.age << endl;
	cout << "p->age=" << p->age << endl;
}

/*  2.const修饰的全局变量具有内部链接属性  */
void test05()
{
	extern const int c; // 如果要建立外部链接也同时必须在外部定义的变量加extern修饰
	cout << c << endl;
}

int main()
{
	test05();

	system("pause");
	return 0;
}
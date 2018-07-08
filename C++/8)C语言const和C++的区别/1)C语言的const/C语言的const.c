#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// 1.C语言的const修饰的变量都有空间
// 2.C语言的全局const修饰的变量具体外部链接属性

const int a = 10; // 常量区，一旦初始化就不能改变

void test()
{
	const int b = 20; // 栈区
	// 一旦初始化不能直接修改，但是可以间接修改

	extern const int c;  // extern 的作用是说明变量/函数在别处定义的,要在此处引用
	printf("%d\n", c);
}

int main()
{
	test();

	system("pause");
	return 0;
}
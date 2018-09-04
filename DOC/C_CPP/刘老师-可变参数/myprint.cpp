#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>//可变参数的头文件



void my_printf01(const char *fmt,...)
{
	const char *tmp = fmt;

	//1.定义可变参数变量
	va_list ap;

	//2.初始化
	//第二个参数要...前面的参数
	va_start(ap, fmt);//告诉编译器从fmt后面开始取参数

	//3.取参数
	while (tmp!=NULL)
	{
		printf("tmp=%s\n", tmp);
		tmp = va_arg(ap, const char *);
	}

	//4.清理
	va_end(ap);

	
}

void my_printf02(const char *fmt, ...)
{


	//1.定义可变参数变量
	va_list ap;

	//2.初始化
	//第二个参数要...前面的参数
	va_start(ap, fmt);//告诉编译器从fmt后面开始取参数

	//3.取参数
	vprintf(fmt, ap);

	//4.清理
	va_end(ap);


}

void test02()
{
	int a = 10;
	const char *str = "aaaabbbbb";
	my_printf02("%d,%s\n", a, str);
}


int main()
{

	//printf("hello=%d,%s\n",10,"aaaa");

	my_printf01("aaa","bbb","ccc");
	test02();
	system("pause");
	return EXIT_SUCCESS;
}


#pragma once
#include<stdio.h>

// 告诉C++编译器，找func函数要以C语言的方式去找
#ifdef __cplusplus
extern "C"{
#endif

	void func();

#ifdef __cplusplus
}
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//断言  条件为假 就终止程序 输出错误信息
//void assert(scalar expression);

int main()
{
	int i = 3;

	printf("i = %d\n", i);

	// abort
	assert(3 != i);

	printf("hello end\n");

	return 0;
}

/*
# gcc -Wall test.c  // 显示所有的警告信息
# gcc -Wall -Werror test.c  // 将警告信息当做错误处理
*/

// 测试程序(-D选项)：
// gcc test.c  -DSIZE=10
// ./a.out


#include <stdio.h>

int main()
{
	printf("SIZE: %d\n", SIZE);

	return 0;
}

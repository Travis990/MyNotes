#include <stdio.h>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"

int main(void)
{
    int a = 15;
    int b = 3;

    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", sub(a, b));
    printf("a * b = %d\n", mul(a, b));
    printf("a / b = %d\n", Mydiv(a, b));

    return 0;
}

/* 静态库的使用:

[root@localhost 3)静态库和静态库]# ls
add.h  div.h  libtest.a  mul.h  README.txt  sub.h  test.c
[root@localhost 3)静态库和静态库]# gcc test.c -L. -I. -ltest -o test
[root@localhost 3)静态库和静态库]# gcc ./test

*/

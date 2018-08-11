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

/*

引用动态库编译成可执行文件（跟静态库方式一样） 
deng@itcast:~/test/6share_test$ gcc test.c -L. -I. -ltest

执行结果发生了错误:

[root@localhost 3)静态库和静态库]# gcc test.c -L. -I. -ltest
[root@localhost 3)静态库和静态库]# ls
add.h  a.out  div.h  libtest.so  mul.h  README.txt  sub.h  test.c
[root@localhost 3)静态库和静态库]# ./a.out
./a.out: error while loading shared libraries: libtest.so: cannot open shared object file: No such file or directory

- 当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路径。此时就需要系统动态载入器(dynamic linker/loader)。
- 对于elf格式的可执行程序，是由ld-linux.so*来完成的，它先后搜索elf文件的 DT_RPATH段 — 环境变量LD_LIBRARY_PATH — /etc/ld.so.cache文件列表 — /lib/, /usr/lib目录找到库文件后将其载入内存。 


3）如何让系统找到动态库

- 拷贝自己制作的共享库到/lib或者/usr/lib(不能是/lib64目录)
- 临时设置LD_LIBRARY_PATH：

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径 

- 永久设置,把export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:库路径，设置到~/.bashrc或者 /etc/profile文件中
- 将其添加到 /etc/ld.so.conf文件中
  编辑/etc/ld.so.conf文件，加入库文件所在目录的路径
  运行ldconfig  -v，该命令会重建/etc/ld.so.cache文件
- 使用符号链接， 但是一定要使用绝对路径
  deng@itcast:~/test/6share_test$ sudo ln -s /home/deng/test/6share_test/libtest.so  /lib/libtest.so

*/

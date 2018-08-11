1）动态库制作

步骤一：生成目标文件，此时要加编译选项：-fPIC（fpic） 

deng@itcast:~/test/5share_lib$ gcc -fPIC -c add.c 

deng@itcast:~/test/5share_lib$ gcc -fPIC -c sub.c

deng@itcast:~/test/5share_lib$ gcc -fPIC -c mul.c

deng@itcast:~/test/5share_lib$ gcc -fPIC -c div.c

参数：-fPIC 创建与地址无关的编译程序（pic，position independent code），是为了能够在多个应用程序间共享。 

步骤二：生成共享库，此时要加链接器选项: -shared（指定生成动态链接库）

deng@itcast:~/test/5share_lib$ gcc -shared add.o sub.o mul.o div.o -o libtest.so

步骤三: 通过nm命令查看对应的函数

deng@itcast:~/test/5share_lib$ nm libtest.so | grep add

00000000000006b0 T add

deng@itcast:~/test/5share_lib$ nm libtest.so | grep sub

00000000000006c4 T sub



ldd查看可执行文件的依赖的动态库




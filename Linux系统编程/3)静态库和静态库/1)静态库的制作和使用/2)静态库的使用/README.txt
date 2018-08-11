2）静态库使用

静态库制作完成之后，需要将.a文件和头文件一定发布给用户。

假设测试文件为main.c，静态库文件为libtest.a头文件为head.h

编译命令：

deng@itcast:~/test/4static_test$ gcc  test.c -L. -I. -ltest -o test

参数说明：

- -L：表示要连接的库所在目录
- -l(大写i)：指定链接时需要的库，去掉前缀和后缀



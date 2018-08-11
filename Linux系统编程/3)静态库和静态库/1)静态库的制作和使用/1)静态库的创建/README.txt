1)静态库制作

步骤1：将c源文件生成对应的.o文件 

deng@itcast:~/test/3static_lib$ gcc -c add.c -o add.o  

deng@itcast:~/test/3static_lib$ gcc -c sub.c -o sub.o 

deng@itcast:~/test/3static_lib$ gcc -c mul.c -o mul.o

deng@itcast:~/test/3static_lib$ gcc -c div.c -o div.o 

步骤2：使用打包工具ar将准备好的.o文件打包为.a文件 libtest.a

deng@itcast:~/test/3static_lib$ ar -rcs libtest.a add.o sub.o mul.o div.o 

在使用ar工具是时候需要添加参数：rcs

- r更新
- c创建
- s建立索引



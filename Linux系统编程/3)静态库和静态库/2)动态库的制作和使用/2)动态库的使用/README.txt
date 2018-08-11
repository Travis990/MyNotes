2）动态库测试

引用动态库编译成可执行文件（跟静态库方式一样） 

deng@itcast:~/test/6share_test$ gcc test.c -L. -I. -ltest

 然后运行：./a.out，发现竟然报错了！！！



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




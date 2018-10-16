libcurl 官网：https://curl.haxx.se/
libcurl也是curl工具使用的库
下载源码
可以到官网下载，更方便的是到github上克隆代码

git clone https://github.com/curl/curl.git

编译和安装
cd curl
./buildconf
./configure
make
sudo make install


安装完毕之后，头文件
/usr/local/include/curl
/usr/local/lib/libcurl.so
可执行命令
/usr/local/bin/curl



另外一种办法是：可以简单的执行
sudo apt-get install curl
安装curl命令，该命令将curl安装/usr/bin
sudo apt-get install libcurl4-openssl-dev
来安装libcurl，libcurl的安装路径
头文件：/usr/include/curl
库目录：/usr/lib
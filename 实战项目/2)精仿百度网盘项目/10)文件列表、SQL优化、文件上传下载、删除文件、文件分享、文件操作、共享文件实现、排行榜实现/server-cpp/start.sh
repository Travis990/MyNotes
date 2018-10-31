#!/bin/bash
# 拷贝nginx的配置文件nginx.conf到默认目录
curPath=$(cd `dirname $0`; pwd)
echo ============= Copy nginx.conf =============
sudo mv /usr/local/nginx/conf/nginx.conf /usr/local/nginx/conf/nginx.conf.old
sudo cp "$curPath/conf/nginx.conf" /usr/local/nginx/conf

echo
echo ============= fastdfs ==============
# 关闭已启动的 tracker 和 storage
"$curPath"/fastdfs.sh stop
# 启动 tracker 和 storage
"$curPath"/fastdfs.sh all
# 重启所有的 cgi程序
echo
echo ============= fastCGI ==============
"$curPath"/fcgi.sh
# 关闭nginx
echo
echo ============= nginx ==============
"$curPath"/nginx.sh stop
# 启动nginx
./nginx.sh start
# 关闭redis
echo
echo ============= redis ==============
"$curPath"/redis.sh stop
# 启动redis
"$curPath"/redis.sh start

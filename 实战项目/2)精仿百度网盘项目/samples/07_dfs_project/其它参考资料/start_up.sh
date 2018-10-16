#拷贝配置文件路径
#./cfg.sh

# 杀死 已经启动的后台CGI程序
kill -9 `ps aux | grep "cgi_bin/login.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/reg.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/md5.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/upload.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/myfiles.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/dealfile.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/sharefiles.cgi" | grep -v grep | awk '{print $2}'`
kill -9 `ps aux | grep "cgi_bin/dealsharefile.cgi" | grep -v grep | awk '{print $2}'`

#启动 必要的业务后台cgi应用程序
spawn-fcgi -a 127.0.0.1 -p 8881 -f ./cgi_bin/login.cgi
spawn-fcgi -a 127.0.0.1 -p 8882 -f ./cgi_bin/reg.cgi
spawn-fcgi -a 127.0.0.1 -p 8883 -f ./cgi_bin/md5.cgi
spawn-fcgi -a 127.0.0.1 -p 8884 -f ./cgi_bin/upload.cgi
spawn-fcgi -a 127.0.0.1 -p 8885 -f ./cgi_bin/myfiles.cgi
spawn-fcgi -a 127.0.0.1 -p 8886 -f ./cgi_bin/dealfile.cgi
spawn-fcgi -a 127.0.0.1 -p 8887 -f ./cgi_bin/sharefiles.cgi
spawn-fcgi -a 127.0.0.1 -p 8888 -f ./cgi_bin/dealsharefile.cgi



#启动MySQL服务器
service mysql restart

# 杀死 已经启动的后台redis服务器
kill -9 `ps aux | grep "redis-server" | grep -v grep | awk '{print $2}'`


#启动redis服务器
redis-server ./conf/redis/redis.conf


#启动nginx服务器
/usr/local/nginx/sbin/nginx -s quit
/usr/local/nginx/sbin/nginx

#启动本地tracker
/usr/bin/fdfs_trackerd ./conf/fdfs/tracker/tracker.conf restart

#启动本地storage
/usr/bin/fdfs_storaged ./conf/fdfs/storage/storage.conf restart

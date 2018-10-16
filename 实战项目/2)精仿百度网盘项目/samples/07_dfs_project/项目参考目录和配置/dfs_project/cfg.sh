#拷贝nginx配置文件到指定目录
cp ./conf/web_server/nginx.conf /usr/local/nginx/conf

#storage_web_server
cp ./conf/fdfs/storage/http.conf /etc/fdfs/
cp ./conf/fdfs/storage/mime.types /etc/fdfs/
cp ./conf/fdfs/storage/mod_fastdfs.conf	/etc/fdfs/

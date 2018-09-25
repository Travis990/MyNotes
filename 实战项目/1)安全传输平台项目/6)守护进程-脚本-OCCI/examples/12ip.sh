#!/bin/bash

#获取命令的输出
IP=$(ifconfig)
#echo "$IP"

#去掉前缀
IP=${IP#*inet addr:}
#echo "$IP"

#去掉后缀
IP=${IP%  Bcast*}
echo $IP

exit 0


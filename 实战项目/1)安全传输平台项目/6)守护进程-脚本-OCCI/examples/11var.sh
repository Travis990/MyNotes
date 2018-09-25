#!/bin/bash

var=/usr/local/bin:/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin

#引用变量
echo $var
echo ${var}

#从var的字符串中第三个字符开始截取到最后
echo ${var:3}
#从var的字符串中 第三个字符开始截取6个字符
echo ${var:3:6}

#计算字符串的长度
echo ${#var}

#替换字符串中第一次出现usr的字符串, 替换成USR
echo ${var/usr/USR}
#替换字符串中所有出现的usr,替换成USR
echo ${var//usr/USR}

#去掉前缀 最短匹配 从字符串中第一次出现地方 去掉前面部分
echo ${var#*usr}
#去掉前缀 最长匹配 字符串从左到右最后一次出现的地方  去掉前面所有部分
echo ${var##*usr}

#去掉后缀 最短匹配 字符串从右到左 第一次出现的地方 去掉后面所有部分
echo ${var%bin*}
#去掉后缀 最长匹配 字符串从右到左 最后一次出现的地方 去掉后面所有的部分
echo ${var%%bin*}

exit 0


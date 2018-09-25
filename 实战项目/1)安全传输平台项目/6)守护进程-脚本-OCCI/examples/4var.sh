#!/bin/bash

#变量的引用:
#${var} 第一种方式
#$var   第二种方式

#shell中的变量是弱类型
#将100赋值给var
var=100
echo "var = $var"
echo "var = ${var}"

#如果字符串中有空格一定要加双引号
var="hello world"
echo $var

var=3.1415926
echo $var

#如果字符串中没有空格 就不用添加双引号
var=hello
echo $var


exit 0

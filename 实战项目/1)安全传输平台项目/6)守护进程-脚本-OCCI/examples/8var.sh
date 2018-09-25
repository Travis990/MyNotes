#!/bin/bash

#特殊变量
#$0 表示脚本名字  $1第一个参数 $2 第二个参数  $n 第n个参数
echo '$0 = ' $0
echo '$1 = ' $1
echo '$2 = ' $2
echo '$3 = ' $3
echo '$4 = ' $4
echo '$5 = ' $5

shift 1

echo '$0 = ' $0
echo '$1 = ' $1
echo '$2 = ' $2
echo '$3 = ' $3
echo '$4 = ' $4
echo '$5 = ' $5


#执行当前目录中另外一个脚本
./2hello.sh


exit 0


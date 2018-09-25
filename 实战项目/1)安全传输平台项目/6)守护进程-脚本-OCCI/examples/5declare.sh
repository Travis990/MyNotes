#!/bin/bash


#声明一个int类型的变量
declare -i var
var=33
echo "var = $var"

#类型报错
#var="hello world"


#声明一个索引数组
declare -a array
array[0]=1
array[1]=2
array[2]="hello world"
array[3]=4
echo ${array[*]}


#声明一个关联数组
declare -A arr
arr["A"]="AAAAA"
arr["B"]="BBBBB"
arr["C"]="CCCCC"
echo ${arr["A"]}

#声明一个变量为只读
declare -r var1=3
echo "var1 = $var1"

#var1=44

#-l 将所有的大写字母改为小写
declare -l var2='ABCDEFGHIJKLMN'
echo $var2


#-u 将所有的小写字母改为大写
declare -u var3='abcdefghijklmn'
echo $var3

exit 0





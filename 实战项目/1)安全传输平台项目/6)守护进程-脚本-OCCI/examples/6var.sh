#!/bin/bash

var=11
echo "var = $var"

#将一个变量的值赋值给另外一个变量 使用变量引用方式
#var1=$var
var1=${var}
echo "var1 = $var1"

#将11abc的值赋值给变量var1
var1=${var}abc
echo "var1 = $var1"

#var1=$varabc
var1=$var"abc"
echo "var1 = $var1"



exit 0

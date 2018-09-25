#!/bin/bash

#取命令的输出
#第一种方式:
#    $(cmd)
#
#第二种方式:
#    `cmd`

#引用一个命令的输出
var=$(ls)
echo "var = $var"

var=`pwd`
echo "var = $var"

exit 0


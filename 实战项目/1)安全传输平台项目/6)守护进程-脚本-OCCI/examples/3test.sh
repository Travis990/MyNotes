#!/bin/bash


pwd
echo "hello world"
ls 
ifconfig

echo "======================="

#如果第一个命令执行失败 那么后面所有的命令都不会执行  &&
ls && ls && ls 

#如果第一个命令执行成功, 那么后面所有的命令都不执行
pwd || pwd || pwd

whoami; whoami; whoami;   

#脚本退出状态码
#返回值之占一个字节
exit 10086

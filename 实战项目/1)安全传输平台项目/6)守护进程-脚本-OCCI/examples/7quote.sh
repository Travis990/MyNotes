#!/bin/bash

#" 会解析转义字符和变量
#' 所有单引号引起来的数据都按照原样输出  不解析
var=123
echo "var = $var"
echo "var = "${var}
echo 'var = $var'

exit 0


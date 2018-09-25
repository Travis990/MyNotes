#!/bin/bash

read -p "please input a number: "  num

#[右边有空格   ]左边有空格
if [ $num -gt 1000 ]
then
    echo "$num > 1000"
else
    echo "$num <= 1000"
fi



exit 0

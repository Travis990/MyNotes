#!/bin/bash
curPath=$(cd `dirname $0`; pwd )
function CheckCMD
{
    cmd="$1"
    if [ -z "`which $cmd`" ]
    then
        return 1
    fi
    return 0
}
function CheckOutRepo
{
    uri="$1"
    repoName=${uri##*/}
    repoName=${repoName%.git}
    if [ ! -d "$repoName" ]
    then
        git clone --depth=1 --recursive "$uri" || return 1
    else
    pushd  "$repoName" 
    git pull --rebase
    git submodule update --init --recursive || return 1
    popd
    fi
}

if CheckCMD git
then
    echo "git installed"
else
    echo "Please install git"
    exit 1
fi

if CheckCMD cmake
then
    echo "cmake installed"
else
    echo "Please install cmake"
    exit 1
fi

pushd "$curPath/dependencies/"
CheckOutRepo https://github.com/Tencent/rapidjson.git || exit 1
#自行封装redis,不再使用cpp_redis
#CheckOutRepo https://github.com/Cylix/cpp_redis.git || exit 1
#因为mysql-connector-cpp源码安装有问题，所以就用源码安装
#CheckOutRepo https://github.com/mysql/mysql-connector-cpp.git || exit 1
echo "sudo apt install libmysqlcppconn-dev"
sudo apt install -y libmysqlcppconn-dev || exit 1
popd 

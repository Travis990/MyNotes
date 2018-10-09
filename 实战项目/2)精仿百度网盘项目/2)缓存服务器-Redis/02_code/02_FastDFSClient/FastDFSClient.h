#pragma once
#include <string>
#include <stdexcept>
namespace itcast
{
    class FastDFSClient
    {
    public:
        //1 构造函数，参数为客户端配置文件地址
        explicit FastDFSClient(std::string cfgFile);
        //2 上传文件的方法，传入参数是本地文件地址，返回值是fileId
        //如果中途有任何出错，以异常的方式抛出
        std::string upload(std::string file) throw(std::runtime_error);  //C++11 语法   编译参数 g++ -std=c++11 ... 
    private:
        //3 记录配置文件地址的私有变量
        std::string mCfgFile;
    };
}

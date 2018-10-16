#pragma once
#include <map>
#include <string>
using namespace std;
namespace itcast
{
//作为所有FastCGI的基类使用
class FastCGIApplication
{
public:
    FastCGIApplication();
    virtual ~FastCGIApplication();

    //当请求是Get方法的时候，run会调用这个函数
    //headers:是FastCGI的各个环境变量的key val值
    virtual void Get(map<string,string> headers);

    //当球球是Post方法的时候，run会调用这个函数
    //headers:是FastCGI的各个环境变量的key val值
    //data:是请求数据的内容
    //len:请求数据的长度
    virtual void Post(map<string,string> headers,char *data,size_t len);

    //FastCGI主要运行函数，类似于Qt的Application::run
    virtual int run();
};
}

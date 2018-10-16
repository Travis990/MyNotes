#include <MakeLog.h>
#include <iostream>
#include <string.h>
#include "FastCGIApplication.h"
#include "FastCGIErrorCode.h"
using namespace std;
using namespace itcast;
#define LOG_MODULE       "cgi"
#define LOG_PROC         "testCGI"
class TestCGI:public FastCGIApplication
{
public:
    void Get(map<string,string>headers)
    {
        //输出header
        cout << "Content-type: text/plain\r\n\r\n";
        for(auto it : headers)
        {
            cout<<it.first<<"="<<it.second<<endl;
        }
    }
    void Post(map<string,string>headers,char *data,size_t len)
    {
        //输出header
        cout << "Content-type: text/plain\r\n\r\n";
        for(auto it : headers)
        {
            cout<<it.first<<"="<<it.second<<endl;
        }

        //输出post数据
        cout<<"stdin data is :"<<endl;
        string content(data,data+len);
        cout<<content<<endl;
        //最终使用curl 命令进行测试,Post方法发送helloworld到服务端
        //curl -d helloworld http://ip/test 
    }
};
int main()
{
    TestCGI app;
    return app.run();
}


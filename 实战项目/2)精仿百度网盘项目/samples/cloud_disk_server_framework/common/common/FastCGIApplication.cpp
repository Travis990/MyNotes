#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
#include "FastCGIApplication.h"
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <cstring>
using namespace std;
namespace itcast
{
FastCGIApplication::FastCGIApplication()
{
}
FastCGIApplication::~FastCGIApplication()
{
}
void FastCGIApplication::Get(map<string,string>)
{
    //默认情况下没有实现该方法统一
    //返回405错误,不支持该方法
    cout<<"Status: 405 Method Not Allowed\r\n";
}

void FastCGIApplication::Post(map<string,string>,char *,size_t)
{
    //默认情况下没有实现该方法统一
    //返回405错误,不支持该方法
    cout<<"Status: 405 Method Not Allowed\r\n";
}
int FastCGIApplication::run()
{
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    //阻塞等待用户连接
    while (FCGX_Accept_r(&request) == 0)
    {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
        cin  = &cin_fcgi_streambuf;
        cout = &cout_fcgi_streambuf;
        cerr = &cerr_fcgi_streambuf;
#else
        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);
#endif

        //分离env的key和value转化
        map<string,string> headers;
        for(auto envStr = request.envp ; *envStr!=nullptr;++envStr)
        {
            string s = *envStr;
            auto pos = s.find('=');
            string key = s.substr(0,pos);
            string value = s.substr(pos+1);
            headers.insert(make_pair(key,value));
        }

        //抽取content_length来操作请求数据
        auto itContentLength = headers.find("CONTENT_LENGTH");
        size_t contentLength = 0;
        if(itContentLength!=headers.end())
        {
            auto strContentLenght = itContentLength->second;
            contentLength = strContentLenght.empty()?0:stoll(strContentLenght);
        }
        //使用智能指针管理内存，自动释放
        unique_ptr<char[]> uptr;
        if(contentLength!=0)
        {
            //有请求数据，将其全部读出放到一块内存
            char *data=new char[contentLength];
            uptr.reset(data);
            size_t read_sum=0;
            for(;!cin.eof()&&read_sum<contentLength;)
            {
                char buf[1024];
                size_t readLen=0;
                memset(buf,0,sizeof(buf));
                cin.read(buf,sizeof(buf));
                readLen = cin.gcount();
                memcpy(data+read_sum,buf,readLen);
                read_sum+=readLen;
            }
            //加保护,特殊情况,如果传输过来的content lenght 和最终读取字节数不符,要防止
            if(read_sum!=contentLength)
            {
                continue;
            }
        }
        //使用智能指针自动释放
        auto requestMethod = headers["REQUEST_METHOD"];
        if(requestMethod=="GET")
        {
            this->Get(headers);
        }
        else if(requestMethod=="POST")
        {
            this->Post(headers,uptr.get(),contentLength);
        }
        else
        {
            //不支持的方法返回405错误
            cout<<"Status: 405 Method Not Allowed\r\n";
        }
    }
#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
    cin  = cin_streambuf;
    cout = cout_streambuf;
    cerr = cerr_streambuf;
#else
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);
#endif

    return 0;
}
}

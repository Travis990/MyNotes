#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
#include "FastCGIApplication.h"
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <cstring>
#include <cassert>
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
    }

    void FastCGIApplication::Post(map<string,string>,char *,size_t)
    {
    }
    int FastCGIApplication::run()
    {
        //参照 fastCGI echo-cpp.cpp 实现程序主循环
        streambuf * cin_streambuf  = cin.rdbuf();
        streambuf * cout_streambuf = cout.rdbuf();
        streambuf * cerr_streambuf = cerr.rdbuf();
        FCGX_Request request;
        FCGX_Init();
        FCGX_InitRequest(&request, 0, 0);
        while (FCGX_Accept_r(&request) == 0)
        {
            // Note that the default bufsize (0) will cause the use of iostream
            // methods that require positioning (such as peek(), seek(),
            // unget() and putback()) to fail (in favour of more efficient IO).
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

            //C 语言fastCGI http请求头从 environ环境变量获取
            //C++ 中使用的 request.envp
            
            map<string,string> headers;
            string contentLength;           //对应Content-length
            string requestMethod;          //对应http请求方法
            //1 提取 request.envp  ，环境变量  key=value 转化为 map<string,string>
            for(int i= 0 ; request.envp[i]!=NULL ; ++i)
            {
                string envStr = request.envp[i]; //key=value  字符串赋值给string
                auto pos = envStr.find("="); //找到=的位置
                string key = envStr.substr(0,pos); //提取key
                string value = envStr.substr(pos+1); //提取value
                headers.insert(make_pair(key,value)); //放到map里边
                
                if(key=="CONTENT_LENGTH")
                {
                    contentLength = value;
                }
                if(key=="REQUEST_METHOD")
                {
                    requestMethod = value;
                }
            }
            //2 提取用户请求数据 通过cin获取，判断有没有用户请求数据，CONTENT_LENGTH
            size_t len;
            if(contentLength.empty())
            {
                //表示没有数据
                len =0 ;
            }
            else
            {
                //将字符串转化为 整型
                len = std::stoull(contentLength);
            }

            //3 请求的方法是Get方法，调用自身的get
            if(requestMethod=="GET") 
            {
                this->Get(headers);
            }
            //4 请求方法是Post方法，调用自身的Post
            if(requestMethod=="POST")
            {
                char *content = nullptr;
                if(len>0)
                {
                    content = new char[len];  //C++11如果new失败会报异常
                }

                //读取用户的请求数据
                cin.read(content,len);
                assert(cin.gcount()==len);

                this->Post(headers,content,len);

                if (content) delete []content;
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
        return 0;
    }
}

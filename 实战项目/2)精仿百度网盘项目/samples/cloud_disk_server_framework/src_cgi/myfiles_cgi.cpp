#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FastCGIApplication.h"
#include "FastCGIErrorCode.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <ConfigHelper.h>
#include "TokenHelper.h"
#include "MakeLog.h"

using namespace std;
using namespace itcast;
using namespace rapidjson;

#define LOG_MODULE       "cgi"
#define LOG_PROC         "myfiles"
#define MEMSET_ARRAY_ZERO(arg)    do{memset(arg,0,sizeof(arg));}while(0);

class MyFilesCGIApplication:public FastCGIApplication
{
public:
    void Post(map<string,string> headers,char *data,size_t len)
    {
        cout << "Content-type: application/json\r\n\r\n";
    }
};

int main()
{
    MyFilesCGIApplication app;
    return app.run();
}

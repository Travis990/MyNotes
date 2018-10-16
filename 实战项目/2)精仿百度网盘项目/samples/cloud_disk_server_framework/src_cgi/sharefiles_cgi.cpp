#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MakeLog.h"
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
#include <TokenHelper.h>
#include <vector>
#include <hiredis.h>

#define LOG_MODULE       "cgi"
#define LOG_PROC         "sharefiles"
#define MEMSET_ARRAY_ZERO(arg)    do{memset(arg,0,sizeof(arg));}while(0);

using namespace std;
using namespace itcast;
using namespace rapidjson;

class ShareFilesCGIApplication:public FastCGIApplication
{
public:
    void Post(map<string,string> headers,char *data , size_t len)
    {
        cout << "Content-type: application/json\r\n\r\n";
    }
};

int main()
{
    ShareFilesCGIApplication app;
    return app.run();
}


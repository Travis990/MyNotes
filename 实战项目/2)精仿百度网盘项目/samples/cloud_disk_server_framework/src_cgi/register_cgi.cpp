#include "MakeLog.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include <memory>

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

using namespace std;
using namespace itcast;
using namespace rapidjson;

#define LOG_MODULE       "cgi"
#define LOG_PROC         "register"

class RegisterCGIApplication:public FastCGIApplication
{
public:
    void Post(map<string,string>,char *data,size_t len)
    {
        cout << "Content-type: application/json\r\n\r\n";
    }
};

int main()
{
    RegisterCGIApplication app;
    return app.run();
}


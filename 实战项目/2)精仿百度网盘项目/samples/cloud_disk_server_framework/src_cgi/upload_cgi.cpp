#include "FastCGIApplication.h"
#include "FastCGIErrorCode.h"
#include "MakeLog.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <FastDFSClient.h>
#include <unistd.h>

#include <ConfigHelper.h>
#include <TokenHelper.h>
#include "MD5Maker.h"

#define LOG_MODULE       "cgi"
#define LOG_PROC         "upload"

using namespace std;
using namespace itcast;
using namespace rapidjson;

class UploadCGIApplication: public FastCGIApplication
{
public:
    void Post(map<string,string> headers,char *data, size_t len)
    {
        cout << "Content-type: application/json\r\n\r\n";
    }
};

int main()
{
    UploadCGIApplication app;
    return app.run();
}

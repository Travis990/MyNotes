#include "MakeLog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "FastCGIApplication.h"
#include "FastCGIErrorCode.h"
#include <sstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <ConfigHelper.h>
#include <TokenHelper.h>

using namespace std;
using namespace itcast;
using namespace rapidjson;

#define LOG_MODULE       "cgi"
#define LOG_PROC         "login"

class LoginCGIApplication:public FastCGIApplication
{
public:
    typedef TokenHelper::LoginInfo LoginInfo;
    LoginCGIApplication()
    {
    }

    LoginInfo ParseRequestJson(const string json)
    {
        Document d;
        if(d.Parse(json.c_str()).HasParseError())
        {
            throw runtime_error(
                    string("parse json "+ json +" error :") +
                    GetParseError_En(d.GetParseError()));
        }
        return {
            d["userName"].GetString(),
            d["passwd"].GetString()
        };
    }

    bool ValidateUser(LoginInfo &info)
    {
        unique_ptr<sql::Connection> con(nullptr);
        bool result = false;
        try
        {
            sql::Driver *driver;
            driver = ::get_driver_instance();
            string mysqlHost = ConfigHelper::getInstance().getVal("mysql","ip");
            string mysqlPort= ConfigHelper::getInstance().getVal("mysql","port");
            string mysqlDBName= ConfigHelper::getInstance().getVal("mysql","database");
            string mysqlUser= ConfigHelper::getInstance().getVal("mysql","user");
            string mysqlPasswd= ConfigHelper::getInstance().getVal("mysql","password");
            con.reset(driver->connect("tcp://"+mysqlHost+":"+mysqlPort,mysqlUser,mysqlPasswd));

            con->setSchema(mysqlDBName);
            unique_ptr<sql::Statement> stmt( con->createStatement());
            stringstream ss;
            ss<<"select id,nickname,phone,email from user where name = '"
                <<info.userName<<"' and password = '"<<info.passwd<<"'";
            unique_ptr<sql::ResultSet> res(stmt->executeQuery(ss.str()));
            if(res->next())
            {
                info.id=res->getUInt("id");
                info.phone = res->getString("phone");
                info.nickName = res->getString("nickname");
                info.email = res->getString("email");
                result = true;
            }
        }
        catch(const sql::SQLException &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"sql exception:%s\n",e.what());
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
        }
        catch(...)
        {
            LOG(LOG_MODULE,LOG_PROC,"unknown exception:%s\n");
        }
        return result;
    }

    void Post(map<string,string>,char *data ,size_t len)
    {
        int resultCode = Succ;
        string token;
        try
        {
            do
            {
                //1 解析输入数据
                string content(data,data+len);
                LOG(LOG_MODULE,LOG_PROC,"data:%s\n",content.c_str());
                auto info = this->ParseRequestJson(content);
                //2 验证用户信息
                if(!this->ValidateUser(info))
                {
                    resultCode = UserInvalid;
                    break;
                }
                LOG(LOG_MODULE,LOG_PROC,"userName:%s passwd:%s , phone :%s id:%d "
                        "email:%s\n",
                        info.userName.c_str(),
                        info.passwd.c_str(),
                        info.phone.c_str(),
                        info.id,
                        info.email.c_str());
                //3 产生token ,不过已经合并到以下方法,存入信息到redis同时返回token
                //4 将token写入到redis
                LOG(LOG_MODULE,LOG_PROC,"token:%s\n",token.c_str());
                token = TokenHelper::WriteInfoToRedis(info);
            }while(0);
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            resultCode=Error;
        }
        //5 返回结果给客户端
        //构建返回结果
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        writer.StartObject();
        writer.Key("code");
        writer.Int(resultCode);
        writer.Key("token");
        writer.String(token.c_str(),static_cast<rapidjson::SizeType>(token.length()));
        writer.EndObject();
        cout << "Content-type: application/json\r\n\r\n";
        cout<<sb.GetString()<<endl;
    }
};

int main()
{
    LoginCGIApplication app;
    return app.run();
}


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
#include "rapidjson/error/en.h"

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
    struct RegisterInfo
    {
        string userName;
        string nickName;
        string phone;
        string passwd;
        string email;
    };

    RegisterInfo getRegisterInfo(string json)
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
            d["nickName"].GetString(),
            d["phone"].GetString(),
            d["passwd"].GetString(),
            d["email"].GetString()
        };
    }
    void Post(map<string,string>,char *data,size_t len)
    {
        int resultCode=Succ;
        unique_ptr<sql::Connection> con(nullptr);
        try{
            do
            {
                //1 解析json
                string content(data,data+len);
                auto regInfo = this->getRegisterInfo(content);

                //2 mysql查询
                sql::Driver *driver;
                driver = ::get_driver_instance();
                string mysqlHost = ConfigHelper::getInstance().getVal("mysql","ip");
                string mysqlPort= ConfigHelper::getInstance().getVal("mysql","port");
                string mysqlDBName= ConfigHelper::getInstance().getVal("mysql","database");
                string mysqlUser= ConfigHelper::getInstance().getVal("mysql","user");
                string mysqlPasswd= ConfigHelper::getInstance().getVal("mysql","password");
                con.reset(driver->connect("tcp://"+mysqlHost+":"+mysqlPort,mysqlUser,mysqlPasswd));
                con->setSchema(mysqlDBName);
                //关闭自动提交--开启事务
                con->setAutoCommit(false);

                unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement("select * from user where name = ?"));
                prepStat->setString(1,regInfo.userName);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                if(res->next())
                {
                    resultCode=UserExists;
                    break;
                }
                //3 mysql插入一条数据到用户表
                prepStat.reset(con->prepareStatement("insert into user(name,nickname,password,phone,createtime,email) values(?,?,?,?,now(),?)"));
                prepStat->setString(1,regInfo.userName);
                prepStat->setString(2,regInfo.nickName);
                prepStat->setString(3,regInfo.passwd);
                prepStat->setString(4,regInfo.phone);
                prepStat->setString(5,regInfo.email);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    break;
                }
                con->commit();
            }while(0);
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            resultCode=Error;
            if(con.get()!=nullptr)
            {
                con->rollback();
            }
        }

        //构建返回结果
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        writer.StartObject();               // Between StartObject()/EndObject(), 
        writer.Key("code");
        writer.Int(resultCode);
        writer.EndObject();
        cout << "Content-type: application/json\r\n\r\n";
        cout<<sb.GetString();
    }
};

int main()
{
    RegisterCGIApplication app;
    return app.run();
}


#include "MakeLog.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/time.h>
#include <memory>
#include <sstream>

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
    struct RegInfo
    {
        string userName;
        string nickName;
        string passwd;
        string phone;
        string email;
    };
    //注意data 是没有\0作为结束符
    RegInfo getUserRegisterInfo(char *data ,size_t len)
    {
        //1 解析json获取客户端传输过来的数据
        Document document;
        //处理data没有\0的问题，构造一个string
        document.Parse(string(data,data+len));
        if(document.HasParseError())
        {
            throw runtime_error(string("Json Parse Excetion:")+GetParseError_En(document.GetParseError()));
        }
        return {
            document["userName"].GetString(),
            document["nickName"].GetString(),
            document["passwd"].GetString(),
            document["phone"].GetString(),
            document["email"].GetString()
        };
    }
    void Post(map<string,string>,char *data,size_t len)
    {
        string mysqlHost = ConfigHelper::getInstance().getVal("mysql","ip");
        string mysqlPort = ConfigHelper::getInstance().getVal("mysql","port");
        string mysqlDB = ConfigHelper::getInstance().getVal("mysql","database");
        string mysqlUser = ConfigHelper::getInstance().getVal("mysql","user");
        string mysqlPasswd = ConfigHelper::getInstance().getVal("mysql","password");
        ResponseCode code = Succ;
        do
        {
            try
            {
                sql::Driver * driver = ::get_driver_instance(); 
                //使用智能指针来管理内存
                unique_ptr<sql::Connection> conn;
                unique_ptr<sql::Statement> stmt;
                unique_ptr<sql::ResultSet> res;

                //从data里边解析出用户传递过来的json
                auto info = getUserRegisterInfo(data,len);
                LOG(LOG_MODULE,LOG_PROC,"Get reginfo %s %s %s %s %s\n",
                        info.userName.c_str(),
                        info.nickName.c_str(),
                        info.passwd.c_str(),
                        info.phone.c_str(),
                        info.email.c_str()
                   );
                //2 查询用户有没有被注册 , 开事务
                conn.reset(driver->connect(mysqlHost+":"+mysqlPort,mysqlUser,mysqlPasswd));
                conn->setSchema(mysqlDB);  //use cloud_disk
                conn->setAutoCommit(false);//关闭数据库的自动提交，使用手动提交，支持事务
                stmt.reset(conn->createStatement());

                std::stringstream ss; //include <sstream> 类似C sprintf
                ss<<"select * from user where name='"<<info.userName<<"' or nickname = '"<<info.nickName<<"'";
                LOG(LOG_MODULE,LOG_PROC,"sql1 : %s\n",ss.str().c_str());
                //执行查询
                res.reset(stmt->executeQuery(ss.str()));

                if(res->next())
                {
                    //用户已经存在
                    LOG(LOG_MODULE,LOG_PROC,"user exists : %s %s\n",info.userName.c_str(),info.nickName.c_str());
                    code = UserExists ;
                    break;
                }
                //3 插入数据到数据库中，完成注册
                //insert into user(name,nickname,password,phone,email,createtime)
                //                values(......,now())
                ss.str("");//清空stringstream
                ss<<"insert into user(name,nickname,password,phone,email,createtime)"
                    <<" values('"<<info.userName<<"','"<<info.nickName
                    <<"','"<<info.passwd<<"','"<<info.phone<<"','"<<info.email<<"',now())";
                LOG(LOG_MODULE,LOG_PROC,"sql2 : %s\n",ss.str().c_str());
                int affactRow = stmt->executeUpdate(ss.str()) ; //返回值影响多少行
                if(affactRow!=1)
                {
                    //报错
                    LOG(LOG_MODULE,LOG_PROC,"sql2 exec fail\n");
                    code = Error;
                    conn->rollback();//回滚事务
                    break;
                }
                //提交事务
                conn->commit();
            }
            catch(const exception &e)
            {
                code = Error;
                LOG(LOG_MODULE,LOG_PROC,"Get excetpion : %s\n",e.what());
            }
        }while(0);
        //4 结果的返回
        cout << "Content-type: application/json\r\n\r\n";
        StringBuffer s;   
        Writer<StringBuffer> writer(s); 
        writer.StartObject();               // 写一个 {
        writer.Key("code");                // output a key, 
        writer.Int(int(code));             // follow by a value.
        writer.EndObject();                 //写一个 }                
        cout << s.GetString() << endl;                                                      

    }
};

int main()
{
    RegisterCGIApplication app;
    return app.run();
}


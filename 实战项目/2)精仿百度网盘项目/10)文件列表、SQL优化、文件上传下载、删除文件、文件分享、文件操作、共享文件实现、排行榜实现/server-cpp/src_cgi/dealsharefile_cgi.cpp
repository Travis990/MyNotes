#include "fcgi_config.h"
#include "fcgi_stdio.h"
#include "MakeLog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
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
#include <TokenHelper.h>
using namespace std;
using namespace itcast;
using namespace rapidjson;

#define LOG_MODULE       "cgi"
#define LOG_PROC         "dealsharefile"

class DealShareFileCGIApplication:public FastCGIApplication
{
public:
    struct RequestData
    {
        string token;
        int shareId;
        string act;
    };
    DealShareFileCGIApplication()
    {
    }

    RequestData ParseRequestJson(string json)
    {
        Document d;
        if(d.Parse(json.c_str()).HasParseError())
        {
            throw runtime_error(
                    string("parse json "+ json +" error :") +
                    GetParseError_En(d.GetParseError()));
        }
        string token = d["token"].GetString();
        string shareId = d["shareId"].GetString();
        string act = d["act"].GetString();
        return 
        {
            token,
            //TODO: 客户端传过来的shareId是string类型，所以还要多转一次
            std::stoi(shareId),
            act
        };
    }
    static sql::Connection *GetMySQLConnection()
    {
        sql::Driver *driver;
        driver = ::get_driver_instance();
        string mysqlHost = ConfigHelper::getInstance().getVal("mysql","ip");
        string mysqlPort= ConfigHelper::getInstance().getVal("mysql","port");
        string mysqlDBName= ConfigHelper::getInstance().getVal("mysql","database");
        string mysqlUser= ConfigHelper::getInstance().getVal("mysql","user");
        string mysqlPasswd= ConfigHelper::getInstance().getVal("mysql","password");
        auto conn = driver->connect("tcp://"+mysqlHost+":"+mysqlPort,mysqlUser,mysqlPasswd);
        conn->setSchema(mysqlDBName);
        return conn;
    }
    int RaisePV(int shareId)
    {
        int resultCode=Succ;
        unique_ptr<sql::Connection> con;
        try
        {
            //打开事务
            con.reset(GetMySQLConnection());
            con->setAutoCommit(false);
            //确认文件存在并且获取文件id
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement(
                        "select pv from share_file_list where id=?"));
            prepStat->setInt64(1,shareId);
            unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
            int pv=0;
            if(!res->next())
            {
                resultCode=FileNotExists;
                throw runtime_error("File Not Exists share id is : " + to_string(shareId));
            }
            else
            {
                pv = res->getInt("pv");
            }

            prepStat.reset(con->prepareStatement(
                        "update share_file_list set pv = ? where id = ? "));
            prepStat->setInt(1,pv+1);
            prepStat->setInt64(2,shareId);
            if(prepStat->executeUpdate()!=1)
            {
                resultCode=Error;
                throw runtime_error("Cannot update share_file_list");
            }
            con->commit();
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
        return resultCode;
    }
    int SaveFileToUser(long long uid , int shareId)
    {
        int resultCode=Succ;
        unique_ptr<sql::Connection> con;
        try
        {
            string fileId;
            string fileName;
            //打开事务
            con.reset(GetMySQLConnection());
            con->setAutoCommit(false);
            //确认文件存在并且获取文件id
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement(
                        "select file_id,filename from share_file_list where id=?"));
            prepStat->setInt64(1,shareId);
            unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
            if(!res->next())
            {
                resultCode=FileNotExists;
                throw runtime_error("File Not Exists");
            }
            else
            {
                fileId=res->getString("file_id");
                fileName=res->getString("filename");
            }

            prepStat.reset(con->prepareStatement(
                        "insert into user_file_list(uid,filename,file_id,createtime,shared_status,pv) values(?,?,?,now(),0,0)"));
            prepStat->setInt64(1,uid);
            prepStat->setString(2,fileName);
            prepStat->setString(3,fileId);
            if(prepStat->executeUpdate()!=1)
            {
                resultCode=Error;
                throw runtime_error("Cannot update share_file_list");
            }
            con->commit();
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
        return resultCode;
    }
    void Post(map<string,string>,char *data ,size_t len)
    {
        int resultCode = Succ;
        string token;
        try
        {
            //1 解析输入数据
            string content(data,data+len);
            auto req = this->ParseRequestJson(content);
            LOG(LOG_MODULE,LOG_PROC,"shareid %d\n",req.shareId);
            //2 验证用户信息
            TokenHelper::LoginInfo userInfo;
            auto succ = TokenHelper::VerifyToken(req.token,userInfo);
            if(!succ)
            {
                resultCode=UserNotLogin;
            }
            else
            {
                //3 根据act来处理
                if(req.act=="save")
                {
                    //转存文件
                    resultCode = this->SaveFileToUser(userInfo.id,req.shareId);
                }
                else if(req.act == "pv")
                {
                    //添加瞎子啊排行
                    resultCode = this->RaisePV(req.shareId);
                }
                else
                {
                    //其他未知行为
                }
            }
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
        writer.EndObject();
        cout << "Content-type: application/json\r\n\r\n";
        cout<<sb.GetString()<<endl;
    }
};

int main()
{
    DealShareFileCGIApplication app;
    return app.run();
}


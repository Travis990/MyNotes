#include "fcgi_config.h"
#include "fcgi_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "MakeLog.h"

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

#define LOG_MODULE       "cgi"
#define LOG_PROC         "md5"

using namespace std;
using namespace itcast;
using namespace rapidjson;

class MD5CGIApplication: public FastCGIApplication
{
public:
    MD5CGIApplication(){};
    struct RequestData
    {
        string token;
        string md5;
        string fileName;
    };
    RequestData ParseInput(string json)
    {
        Document d;
        if(d.Parse(json.c_str()).HasParseError())
        {
            throw runtime_error(
                    string("parse json "+ json +" error :") +
                    GetParseError_En(d.GetParseError()));
        }
        return {
            d["token"].GetString(),
            d["md5"].GetString(),
            d["fileName"].GetString()
        };
    }
    //成功返回true，失败返回false
    int FindFileThenAddUserFile(const long long uid,const string md5,const string fileName)
    {
        unique_ptr<sql::Connection> con(nullptr);
        sql::Driver *driver;
        driver = ::get_driver_instance();
        string mysqlHost = ConfigHelper::getInstance().getVal("mysql","ip");
        string mysqlPort= ConfigHelper::getInstance().getVal("mysql","port");
        string mysqlDBName= ConfigHelper::getInstance().getVal("mysql","database");
        string mysqlUser= ConfigHelper::getInstance().getVal("mysql","user");
        string mysqlPasswd= ConfigHelper::getInstance().getVal("mysql","password");
        con.reset(driver->connect("tcp://"+mysqlHost+":"+mysqlPort,mysqlUser,mysqlPasswd));

        con->setSchema(mysqlDBName);
        //打开事务，关闭自动提交
        con->setAutoCommit(false);
        //1 写file_info表,存储文件基本信息
        unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement("select file_id,count from file_info where md5 = ?"));
        prepStat->setString(1,md5.c_str());
        unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
        string fileId;
        int count;
        if(res->next())
        {
            fileId= res->getString("file_id");
            count = res->getInt("count");
        }
        else
        {
            LOG(LOG_MODULE,LOG_PROC,"md5:%s not exists\n",md5.c_str());
            return FileNotExists;
        }

        //2 写user_file_list表，存储用户和文件的关系信息
        //查询用户是否已经存在同名文件
        prepStat.reset(con->prepareStatement("select * from user_file_list where uid = ? and filename=?"));
        prepStat->setInt64(1,uid);
        prepStat->setString(2,fileName);
        res.reset(prepStat->executeQuery());
        if(res->next())
        {
            LOG(LOG_MODULE,LOG_PROC,"filename:%s uid:%ld exists\n",fileName.c_str(),uid);
            return FileExists;
        }
        //3插入新数据
        prepStat.reset(con->prepareStatement("insert into user_file_list(uid,filename,file_id,createtime) values(?,?,?,now())"));
        prepStat->setInt64(1,uid);
        prepStat->setString(2,fileName);
        prepStat->setString(3,fileId);
        if(prepStat->executeUpdate()!=1)
        {
            throw runtime_error(string("Cannot insert user_file_list")+to_string(uid)+fileName+fileId);
        }
        
        //4 更新file_info 中的count
        prepStat.reset(con->prepareStatement("update file_info set count=? where file_id=?"));
        prepStat->setInt(1,count+1);
        prepStat->setString(2,fileId);
        if(prepStat->executeUpdate()!=1)
        {
            throw runtime_error("Cannot update file_info");
        }
        con->commit();
        return Succ;
    }

    void Post(map<string,string>,char *data, size_t len)
    {
        int resultCode=Succ;
        try
        {
            //1 解析输入数据
            string content(data,data+len);
            auto request = this->ParseInput(content);
            //2 验证token
            TokenHelper::LoginInfo userInfo;
            auto succ = TokenHelper::VerifyToken(request.token,userInfo);
            if(!succ)
            {
                resultCode = UserNotLogin;
            }
            else
            {
                //3 查询MD5并且转存为用户文件
                resultCode = FindFileThenAddUserFile(userInfo.id,request.md5,request.fileName);
            }
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
        }
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
    MD5CGIApplication app;
    return app.run();
}


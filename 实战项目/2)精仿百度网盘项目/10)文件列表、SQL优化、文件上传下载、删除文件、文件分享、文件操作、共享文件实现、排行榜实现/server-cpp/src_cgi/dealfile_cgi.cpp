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

#define LOG_MODULE       "cgi"
#define LOG_PROC         "dealfile"

using namespace std;
using namespace itcast;
using namespace rapidjson;

class DealFileCGIApplication:public FastCGIApplication
{
    public:
        DealFileCGIApplication()
        {
        }

        struct RequestData
        {
            string token;
            string fileName;
            string act;
        };
        RequestData ParseRequestJson(string json)
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
                    d["fileName"].GetString(),
                    d["act"].GetString()
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
        int ShareFile(long long userId ,string fileName)
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
                            "select file_id from user_file_list where uid=? and filename = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                string fileId;
                if(!res->next())
                {
                    resultCode=FileNotExists;
                    throw runtime_error("File Not Exists");
                }
                else
                {
                    fileId = res->getString("file_id");
                }
                //确保没有人已经共享了这个文件
                prepStat.reset(con->prepareStatement("select * from share_file_list where file_id = ? "));
                prepStat->setString(1,fileId);
                res.reset(prepStat->executeQuery());
                if(res->next())
                {
                    //如果已经有人共享了这个文件，那就进制继续共享
                    resultCode=FileExists;
                    throw runtime_error("Share File Exists");
                }

                prepStat.reset(con->prepareStatement(
                    "update user_file_list set shared_status = 1 where uid = ? and  filename = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    throw runtime_error("Cannot Update user_file_list");
                }

                prepStat.reset(con->prepareStatement(
                            "insert into share_file_list (uid, file_id, createtime, filename, pv) values (?, ?, now(), ?, ?)"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileId);
                prepStat->setString(3,fileName);
                prepStat->setInt(4,0);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    throw runtime_error("Cannot Insert share_file_list");
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
        int CancelShareFile(long long userId, string fileName)
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
                            "select file_id from user_file_list where uid=? and filename = ? "));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                string fileId;
                if(!res->next())
                {
                    resultCode=FileNotExists;
                    throw runtime_error("File Not Exists");
                }
                else
                {
                    fileId = res->getString("file_id");
                }

                prepStat.reset(con->prepareStatement(
                            "delete from share_file_list where uid = ? and file_id = ? "));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileId);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    throw runtime_error("Cannot Delete from share_file_list");
                }

                prepStat.reset(con->prepareStatement(
                            "update user_file_list set shared_status = 0 where uid = ? and filename = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    throw runtime_error("Cannot Update user_file_list");
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
        int RemoveFile(long long userId,string fileName)
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
                            "select file_id from user_file_list where uid=? and filename = ? "));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                string fileId;
                if(!res->next())
                {
                    throw runtime_error("File Not Exists");
                }
                else
                {
                    fileId = res->getString("file_id");
                }

                //首先确认是否有在分享
                prepStat.reset(con->prepareStatement(
                            "select * from share_file_list where uid = ? and file_id = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileId);
                res.reset(prepStat->executeQuery());
                if(res->next())
                {
                    //如果已经分享，那么就要清理分享
                    prepStat.reset(con->prepareStatement(
                                "update user_file_list set shared_status = 0 where uid = ? and filename = ?"));
                    prepStat->setInt64(1,userId);
                    prepStat->setString(2,fileName);
                    if(prepStat->executeUpdate()!=1)
                    {
                        throw runtime_error("Cannot Update user_file_list");
                    }

                    prepStat.reset(con->prepareStatement(
                                "delete from share_file_list where uid = ? and file_id = ?"));
                    prepStat->setInt64(1,userId);
                    prepStat->setString(2,fileId);
                    if(prepStat->executeUpdate()!=1)
                    {
                        throw runtime_error("Cannot Delete from share_file_list");
                    }
                }

                //清理user_file_list信息
                prepStat.reset(con->prepareStatement(
                            "delete from user_file_list where uid = ? and  filename = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                if(prepStat->executeUpdate()!=1)
                {
                    throw runtime_error("Cannot Delete from user_file_list");
                }
                //将file_info中的count-1
                prepStat.reset(con->prepareStatement(
                            "select count from file_info where file_id= ?"));
                prepStat->setString(1,fileId);
                res.reset(prepStat->executeQuery());
                int count = 0;
                if(res->next())
                {
                    count = res->getInt("count");
                }
                else
                {
                    throw runtime_error("Cannot query count from file_info");
                }
                
                prepStat.reset(con->prepareStatement(
                            "update file_info set count=? where file_id= ?"));
                prepStat->setInt(1,count-1);
                prepStat->setString(2,fileId);
                if(prepStat->executeUpdate()!=1)
                {
                    throw runtime_error("Cannot update file_info");
                }
                //提交事务
                con->commit();
            }
            catch(const exception &e)
            {
                LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
                con->rollback();
                resultCode=Error;
            }
            return resultCode;
        }
        int RaisePV(long long userId,string fileName)
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
                            "select pv from user_file_list where uid = ? and filename = ?"));
                prepStat->setInt64(1,userId);
                prepStat->setString(2,fileName);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                int pv=0;
                if(!res->next())
                {
                    resultCode=FileNotExists;
                    throw runtime_error("File Not Exists");
                }
                else
                {
                    pv = res->getInt("pv");
                }

                prepStat.reset(con->prepareStatement(
                            "update user_file_list set pv = ? where uid = ? and filename = ?"));
                prepStat->setInt(1,pv+1);
                prepStat->setInt64(2,userId);
                prepStat->setString(3,fileName);
                if(prepStat->executeUpdate()!=1)
                {
                    resultCode=Error;
                    throw runtime_error("Cannot Delete from share_file_list");
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
        void Post(map<string,string>,char*data,size_t len)
        {
            int resultCode=Succ;
            try
            {
                //1 解析输入数据
                string content(data,data+len);
                auto request = this->ParseRequestJson(content);
                //2 验证用户登录
                TokenHelper::LoginInfo loginInfo;
                auto succ = TokenHelper::VerifyToken(request.token,loginInfo);
                if(!succ)
                {
                    resultCode = UserNotLogin;
                }
                else
                {
                    if(request.act=="share")
                    {
                        resultCode = this->ShareFile(loginInfo.id,request.fileName);
                    }
                    else if(request.act=="cancelShare")
                    {
                        resultCode = this->CancelShareFile(loginInfo.id,request.fileName);
                    }
                    else if(request.act=="remove")
                    {
                        resultCode = this->RemoveFile(loginInfo.id,request.fileName);
                    }
                    else if(request.act=="pv")
                    {
                        resultCode = this->RaisePV(loginInfo.id,request.fileName);
                    }
                    else
                    {
                        throw runtime_error("Unrecognized act "+request.act);
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
    DealFileCGIApplication app;
    return app.run();
}


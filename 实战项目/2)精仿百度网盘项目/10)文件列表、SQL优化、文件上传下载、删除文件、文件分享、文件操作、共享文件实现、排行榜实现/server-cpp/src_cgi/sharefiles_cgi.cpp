#include "fcgi_config.h"
#include "fcgi_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    struct RequestData
    {
        string token;
        int start;
        int count;
        string act;
    };
    struct ShareFileInfo
    {
        int shareId;
        string user;
        string fileName;
        string md5;
        string url;
        size_t size;
        string type;
        size_t pv;
    };
    ShareFilesCGIApplication()
    {
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
            d["start"].GetInt(),
            d["count"].GetInt(),
            d["act"].GetString()
        };
    }

    StringBuffer GetRankingList(int skip, int count)
    {
        unique_ptr<sql::Connection> con;
        try
        {
            //1 首先先查询一下redis有没有
            vector<ShareFileInfo> vecRankingList;
            if(!this->GetRankingListFromRedis(vecRankingList))
            {
                con.reset(GetMySQLConnection());
                //查询列表
                string storageWebSrvIpPort = ConfigHelper::getInstance().getVal("storage_web_server","ip")+":"+ConfigHelper::getInstance().getVal("storage_web_server","port");
                unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement(
                            "select concat('http://"+storageWebSrvIpPort+"/',file_id) as url, filename, pv from share_file_list order by pv desc limit ?,?"));
                prepStat->setInt(1,skip);
                prepStat->setInt(2,count);
                unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
                while(res->next())
                {
                    ShareFileInfo fileInfo;
                    fileInfo.fileName = res->getString("filename");
                    fileInfo.pv = res->getUInt64("pv");
                    vecRankingList.push_back(fileInfo);
                }
                this->SaveRankingListToRedis(vecRankingList);
            }

            StringBuffer sb;
            Writer<StringBuffer> writer(sb);
            writer.StartObject();
            writer.Key("code");
            writer.Int(Succ);
            writer.Key("files");
            writer.StartArray();
            for(auto item : vecRankingList)
            {
                writer.StartObject();
                writer.Key("fileName");
                writer.String(item.fileName);
                writer.Key("pv");
                writer.Uint64(item.pv);
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();
            return sb;
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
        return StringBuffer();
    }

    void SaveRankingListToRedis(vector<ShareFileInfo> vec) throw(runtime_error)
    {
        string errStr;
        redisContext *conn=nullptr;
        do
        {
            StringBuffer sb;
            Writer<StringBuffer> writer(sb);
            writer.StartArray();
            for(auto item : vec)
            {
                writer.StartObject();
                writer.Key("fileName");
                writer.String(item.fileName);
                writer.Key("pv");
                writer.Int(item.pv);
                writer.EndObject();
            }
            writer.EndArray();

            string redisIp = ConfigHelper::getInstance().getVal("redis","ip");
            string redisPort = ConfigHelper::getInstance().getVal("redis","port");
            conn = redisConnect(redisIp.c_str(),stoll(redisPort));
            if(!conn||conn->err)
            {
                //1 redis连接出错
                if (conn) {
                    errStr = std::string("Connect error:")+conn->errstr;
                } else {
                    errStr = "Connection error: can't allocate redis context\n";
                }
                break;
            }
            //存json 同时设置超时时间为1分钟
            redisReply *ptrRep = (redisReply*)redisCommand(conn,
                    "setex cloud_disk_ranking_list_json %d %s",
                    60,
                    sb.GetString()
                    );
            //4 结果集处理
            if(!ptrRep)
            {
                errStr ="Cannot get reply obj";
                break;
            }
            if(ptrRep->type!=REDIS_REPLY_STATUS||string("OK")!=ptrRep->str)
            {
                errStr = "set command fail";
                break;
            }
        }
        while(0);
        if(conn)
            redisFree(conn);
        if(!errStr.empty())
        {
            throw runtime_error(errStr);
        }
    }
    bool GetRankingListFromRedis(vector<ShareFileInfo> &outVec)
    {
        vector<ShareFileInfo> vec;
        string errStr;
        bool ret = true;
        redisContext *conn=nullptr;
        do
        {
            string redisIp = ConfigHelper::getInstance().getVal("redis","ip");
            string redisPort = ConfigHelper::getInstance().getVal("redis","port");
            conn = redisConnect(redisIp.c_str(),stoll(redisPort));
            if(!conn||conn->err)
            {
                //1 redis连接出错
                if (conn) {
                    errStr = std::string("Connect error:")+conn->errstr;
                } else {
                    errStr = "Connection error: can't allocate redis context\n";
                }
                break;
            }
            redisReply *ptrRep = (redisReply*)redisCommand(conn,
                    "get cloud_disk_ranking_list_json");
            //4 结果集处理
            if(!ptrRep)
            {
                errStr ="Cannot get reply obj";
                break;
            }
            if(ptrRep->type==REDIS_REPLY_NIL)
            {
                //redis没有设置该值,正常返回
                ret = false;
                break;
            }
            else if(ptrRep->type!=REDIS_REPLY_STRING)
            {
                errStr = "get command fail";
                break;
            }
            Document doc;
            doc.Parse(ptrRep->str);
            auto arr = doc.GetArray();
            for(size_t i = 0 ; i< arr.Size() ; ++i)
            {
                auto obj = arr[i].GetObject();
                ShareFileInfo fileInfo;
                fileInfo.fileName = obj["fileName"].GetString();
                fileInfo.pv = obj["pv"].GetUint64();
                vec.push_back(fileInfo);
            }
        }
        while(0);
        if(conn)
            redisFree(conn);
        if(!errStr.empty())
        {
            throw runtime_error(errStr);
        }
        vec.swap(outVec);
        return ret;
    }
    StringBuffer GetShareFileList(int skip,int count)
    {
        unique_ptr<sql::Connection> con;
        try
        {
            con.reset(GetMySQLConnection());
            string storageWebSrvIpPort = ConfigHelper::getInstance().getVal("storage_web_server","ip")+":"+ConfigHelper::getInstance().getVal("storage_web_server","port");
            //查询列表
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement(
                        "select "
                        "user.name,"
                        "share_file_list.id,"
                        "file_info.md5,"
                        "date_format(share_file_list.createtime,'%Y-%m-%d %h:%i:%s') as createtime,"
                        "concat('http://"+storageWebSrvIpPort+"/',share_file_list.file_id) as url,"
                        "share_file_list.filename,"
                        "file_info.size,"
                        "file_info.type,"
                        "share_file_list.pv "
                        "from file_info,share_file_list,user "
                        "where file_info.file_id = share_file_list.file_id and user.id=share_file_list.uid limit ?,?"));
            prepStat->setInt(1,skip);
            prepStat->setInt(2,count);
            unique_ptr<sql::ResultSet> res(prepStat->executeQuery());

            StringBuffer sb;
            Writer<StringBuffer> writer(sb);
            writer.StartObject();
            writer.Key("code");
            writer.Int(Succ);
            writer.Key("files");
            writer.StartArray();

            while(res->next())
            {
                writer.StartObject();

                writer.Key("user");
                writer.String(res->getString("name"));

                writer.Key("shareId");
                writer.String(res->getString("id"));

                writer.Key("fileName");
                writer.String(res->getString("filename"));

                writer.Key("md5");
                writer.String(res->getString("md5"));

                writer.Key("url");
                writer.String(res->getString("url"));

                writer.Key("size");
                writer.String(res->getString("size"));

                writer.Key("type");
                writer.String(res->getString("type"));

                writer.Key("pv");
                writer.Int(res->getInt("pv"));
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();

            return sb;
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
        return StringBuffer();
    }
    StringBuffer GetShareFileCount()
    {
        unique_ptr<sql::Connection> con;
        try
        {
            con.reset(GetMySQLConnection());
            //查询列表
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement(
                        "select count(*) as count from share_file_list "));
            unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
            res->next();
            int count = res->getInt("count");
            StringBuffer sb;
            Writer<StringBuffer> writer(sb);
            writer.StartObject();
            writer.Key("code");
            writer.Int(Succ);
            writer.Key("count");
            writer.Int(count);
            writer.EndObject();
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
    }
    void Post(map<string,string> headers,char *data , size_t len)
    {
        int resultCode = Succ;
        string token;
        StringBuffer sb;
        try
        {
            //1 解析输入数据
            string content(data,data+len);
            auto req = this->ParseRequestJson(content);
            TokenHelper::LoginInfo userInfo;
            auto succ = TokenHelper::VerifyToken(req.token,userInfo);
            if(!succ)
            {
                resultCode = UserNotLogin;
            }
            else
            {
                //获取共享文件列表
                if(req.act=="list")
                {
                    sb = this->GetShareFileList(req.start,req.count);
                }
                //获取共享文件下载榜
                else if(req.act=="rank")
                {
                    sb = this->GetRankingList(req.start,req.count);
                }
                //获取共享文件数量
                else if(req.act=="count")
                {
                    sb = this->GetShareFileCount();
                }
            }
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            resultCode=Error;
            Writer<StringBuffer> writer(sb);
            writer.StartObject();
            writer.Key("code");
            writer.Int(resultCode);
            writer.EndObject();
        }
        //5 返回结果给客户端
        cout << "Content-type: application/json\r\n\r\n";
        cout<<sb.GetString();
    }
};

int main()
{
    ShareFilesCGIApplication app;
    return app.run();
}


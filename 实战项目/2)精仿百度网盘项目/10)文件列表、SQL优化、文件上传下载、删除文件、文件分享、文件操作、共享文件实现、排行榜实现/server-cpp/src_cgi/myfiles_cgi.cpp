#include "fcgi_config.h"
#include "fcgi_stdio.h"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#include "TokenHelper.h"
#include "MakeLog.h"

using namespace std;
using namespace itcast;
using namespace rapidjson;

#define LOG_MODULE       "cgi"
#define LOG_PROC         "myfiles"
#define MEMSET_ARRAY_ZERO(arg)    do{memset(arg,0,sizeof(arg));}while(0);

class MyFilesCGIApplication:public FastCGIApplication
{
public:
    struct FileInfo
    {
        string fileName;
        string md5;
        string fileId;
        long long size;
        string type;
        int pv;
        int shareStat;
        string createTime;
    };
    MyFilesCGIApplication(){}
    string GetFileUrl(string fileId)
    {
        stringstream ss;
        ss<<"http://"<<ConfigHelper::getInstance().getVal("storage_web_server","ip")
            <<':'<<ConfigHelper::getInstance().getVal("storage_web_server","port")
            <<'/'<<fileId;
        return ss.str();
    }
    string ParseGetToken(string json)
    {
        Document d;
        if(d.Parse(json.c_str()).HasParseError())
        {
            throw runtime_error(
                    string("parse json "+ json +" error :") +
                    GetParseError_En(d.GetParseError()));
        }
        return d["token"].GetString();
    }
    vector<FileInfo> GetUserFileList(unsigned int uid)
    {
        unique_ptr<sql::Connection> con(nullptr);
        vector<FileInfo> vecFileList;
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
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement("select uid,filename,a.file_id,md5,size,type,date_format(a.createtime,'%%Y-%%m-%%d %%h:%%i:%%s') as createtime,shared_status,pv from user_file_list a join file_info b on a.file_id=b.file_id where uid = ?"));
            prepStat->setUInt(1,uid);
            unique_ptr<sql::ResultSet> res(prepStat->executeQuery());
            while(res->next())
            {
                FileInfo info ;
                info.fileName =  res->getString("filename");
                info.fileId =  res->getString("file_id");
                info.md5 =  res->getString("md5");
                info.size =  res->getInt64("size");
                info.type =  res->getString("type");
                info.createTime = res->getString("createtime");
                info.shareStat = res->getInt("shared_status");
                info.pv = res->getInt("pv");
                vecFileList.push_back(info);
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
        return vecFileList;
    }
    void Post(map<string,string> headers,char *data,size_t len)
    {
        int resultCode = Succ;
        string token;
        vector<FileInfo> vecFileList;
        try
        {
            do
            {
                //1 解析输入数据
                string content(data,data+len);
                auto token = this->ParseGetToken(content);
                //2 验证用户信息
                TokenHelper::LoginInfo info;
                auto succ = TokenHelper::VerifyToken(token,info);
                if(!succ)
                {
                    resultCode=UserNotLogin;
                }
                else
                {
                    //3 查询用户文件
                    vecFileList = this->GetUserFileList(info.id);
                }
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
        writer.StartObject();               // Between StartObject()/EndObject(), 
        writer.Key("code");
        writer.Int(resultCode);
        if(resultCode==Succ)
        {
            writer.Key("files");
            writer.StartArray();
            //循环构建每一条信息
            for(auto it : vecFileList)
            {
                writer.StartObject();
                writer.Key("fileName");
                writer.String(it.fileName.c_str(),static_cast<unsigned int>(it.fileName.length()));
                writer.Key("type");
                writer.String(it.type.c_str(),static_cast<unsigned int>(it.type.length()));
                writer.Key("md5");
                writer.String(it.md5.c_str(),static_cast<unsigned int>(it.md5.length()));
                writer.Key("createTime");
                writer.String(it.createTime.c_str(),static_cast<unsigned int>(it.createTime.length()));
                writer.Key("size");
                writer.Int64(it.size);
                //URL要添加web服务器地址来来转换
                writer.Key("url");
                string url = this->GetFileUrl(it.fileId);
                writer.String(url.c_str(),static_cast<unsigned int>(url.length()));
                writer.Key("shareStat");
                writer.Int(it.shareStat);
                writer.Key("pv");
                writer.Int(it.pv);
                writer.EndObject();
            }
            writer.EndArray();
        }
        writer.EndObject();
        cout << "Content-type: application/json\r\n\r\n";
        cout << sb.GetString() << endl;
    }
};

int main()
{
    MyFilesCGIApplication app;
    return app.run();
}

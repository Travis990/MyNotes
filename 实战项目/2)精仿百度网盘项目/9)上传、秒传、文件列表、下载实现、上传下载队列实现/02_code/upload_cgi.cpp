#include "fcgi_config.h"
#include "fcgi_stdio.h"
#include "fdfs_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <stdexcept>

#include "MakeLog.h"
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
#include <FastDFSClient.h>

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
    struct RequestFileInfo
    {
        string fileName;
        string token;
        string contentType;
        vector<char> data;
        string fileId;
        string md5;
    };
    UploadCGIApplication(){};
    /**
     * @brief  在字符串full_data中查找字符串substr第一次出现的位置
     *
     * @param full_data 	源字符串首地址
     * @param full_data_len 源字符串长度
     * @param substr        匹配字符串首地址
     *
     * @returns   
     *      成功: 匹配字符串首地址
     *      失败：NULL
     */
    static char* memstr(char* full_data, size_t full_data_len, char* substr) 
    { 
        //异常处理
        if (full_data == NULL || full_data_len <= 0 || substr == NULL) 
        { 
            return NULL; 
        } 

        if (*substr == '\0')
        { 
            return NULL; 
        } 

        //匹配子串的长度
        auto sublen = strlen(substr); 

        size_t i; 
        char* cur = full_data; 
        auto last_possible = full_data_len - sublen + 1; //减去匹配子串后的长度
        for (i = 0; i < last_possible; i++) 
        { 
            if (*cur == *substr) 
            { 
                if (memcmp(cur, substr, sublen) == 0) 
                { 
                    //found  
                    return cur; 
                } 
            }

            cur++; 
        } 

        return NULL; 
    } 
    RequestFileInfo RecvFile(char *multiData,long len)
    {
        RequestFileInfo info;
        char boundary[1024];
        memset(boundary,0,sizeof(boundary));

        char *start = multiData;
        //第一行是boundary
        char *end = strstr(start,"\r\n");
        if(!end)
        {
            LOG(LOG_MODULE, LOG_PROC, "Cannot find boundary \n");
            throw runtime_error("Cannot find boundary");
        }
        strncpy(boundary,start,static_cast<size_t>(end-start));
        start=end +2;
        //跳到token
        end = strstr(multiData,"token=");
        if(!end)
        {
            LOG(LOG_MODULE, LOG_PROC, "Cannot find keyword 'token='\n");
            throw runtime_error("Cannot find keyword 'token=");
        }
        start=end+strlen("token=")+1;
        end = strchr(start,'"');
        info.token = string(start,end);
        start=end+1;

        //跳到Content-type: text/plain\r\n
        end = strstr(multiData,"Content-Type:");
        if(!end)
        {
            //content type 不是 硬需求
            LOG(LOG_MODULE, LOG_PROC, "Cannot find keyword 'Content-Type:' \n");
            //return -1;
        }
        else
        {
            start=end+strlen("Content-Type:")+1;
            end = strstr(start,"\r\n");
            info.contentType = string (start , end);
        }

        //跳到文件名
        end = strstr(multiData,"filename=");
        if(!end)
        {
            LOG(LOG_MODULE, LOG_PROC, "Cannot find keyword 'filename=' \n");
            throw runtime_error("Cannot find keyword 'filename=");
        }
        start=end+strlen("filename=")+1;
        end = strchr(start,'"');
        info.fileName = string (start,end);
        start=end+1;
        //跳过空行
        end = strstr(multiData,"\r\n\r\n");
        start = end + 4;

        //找到boundary
        end=memstr(start,static_cast<size_t>(len-(start-multiData)),boundary);
        if(!end)
        {
            LOG(LOG_MODULE, LOG_PROC, "Cannot find boundary end  \n");
            throw runtime_error("Cannot find boundary end  \n");
        }
        //减去boundary之前的\r\n，这个\r\n是http自己加进去的
        end-=2;
        info.data = vector<char>(start,end);
        return info;
    }

    void SaveFileInfoToDB(RequestFileInfo fileInfo,TokenHelper::LoginInfo userInfo)
    {
        unique_ptr<sql::Connection> con(nullptr);
        try
        {
            //获取驱动
            sql::Driver *driver;
            driver = ::get_driver_instance();
            //读取配置文件获取连接参数
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
            unique_ptr<sql::PreparedStatement> prepStat(con->prepareStatement("insert into file_info(file_id,md5,size,type,count,createtime) values(?,?,?,?,1,now())"));
            prepStat->setString(1,fileInfo.fileId);
            prepStat->setString(2,fileInfo.md5);
            prepStat->setUInt64(3,fileInfo.data.size());
            prepStat->setString(4,fileInfo.contentType);
            if(prepStat->executeUpdate()!=1)
            {
                throw runtime_error("Cannot insert file_info , fileId:"+fileInfo.fileId+" md5:"+fileInfo.md5+" size:"+to_string(fileInfo.data.size()) + " type:"+fileInfo.contentType);
            }

            //2 写user_file_list表，存储用户和文件的关系信息
            prepStat.reset(con->prepareStatement("insert into user_file_list(uid,filename,file_id,createtime) values(?,?,?,now())"));
            prepStat->setInt64(1,userInfo.id);
            prepStat->setString(2,fileInfo.fileName);
            prepStat->setString(3,fileInfo.fileId);
            if(prepStat->executeUpdate()!=1)
            {
                throw runtime_error("Cannot insert user_file_list");
            }
            con->commit();
        }
        catch(const exception &e)
        {
            LOG(LOG_MODULE,LOG_PROC,"exception:%s\n",e.what());
            con->rollback();
        }
    }

    void Post(map<string,string> headers,char *data, size_t len)
    {
        int resultCode=Succ;
        try
        {
            do
            {
                //1 解析输入数据,获取文件信息和token
                auto fileInfo = this->RecvFile(data,len);

                //2 验证token
                TokenHelper::LoginInfo userInfo;
                auto succ = TokenHelper::VerifyToken(fileInfo.token,userInfo);
                if(!succ)
                {
                    resultCode = UserNotLogin;
                    break;
                }
                //3 将上传的文件保存到本地
                char tmpFileName[]="/tmp/cgi_upload_file_XXXXXX";
                int tempFd=mkstemp(tmpFileName);
                if(tempFd==-1)
                {
                    LOG(LOG_MODULE, LOG_PROC, "mkstemp fail\n");
                    throw runtime_error("mkstemp fail");
                }
                for(size_t writeSum = 0 ;writeSum<fileInfo.data.size();)
                {
                    int writeln = write(tempFd , fileInfo.data.data(),static_cast<size_t>(fileInfo.data.size()));
                    if(writeln<=0)
                    {
                        close(tempFd);
                        throw runtime_error("error in write file to tmpfile");
                    }
                    else 
                    {
                        writeSum+=writeln;
                    }
                }
                close(tempFd);
                //4 将文件上传到fastDFS
                string fdfsCfg = ConfigHelper::getInstance().getVal("dfs_path","client");
                FastDFSClient fdfsClient(fdfsCfg);
                string fileId = fdfsClient.upload(tmpFileName);
                fileInfo.fileId = fileId;
                //删除临时文件，免得一直占用空间
                unlink(tmpFileName);
                if(resultCode!=0)
                {
                    LOG(LOG_MODULE, LOG_PROC, "my_fdfs_upload_file return non zero \n");
                    resultCode= 1;
                    throw runtime_error("my_fdfs_upload_file return non zero \n");
                }
                //5 计算md5
                MD5Maker md5(reinterpret_cast<unsigned char*>(fileInfo.data.data()),fileInfo.data.size());
                fileInfo.md5 = md5.getDigestHexString();
                LOG(LOG_MODULE, LOG_PROC, "get file md5 %s\n",fileInfo.md5.c_str());
                //6 写数据库
                this->SaveFileInfoToDB(fileInfo,userInfo);
            }while(0);
        }
        catch(const exception &e)
        {
            resultCode = Error;
            LOG(LOG_MODULE, LOG_PROC, "other exception: %s\n",e.what());
        }
        LOG(LOG_MODULE, LOG_PROC, "result code:%d\n",resultCode);
        //5 返回结果给客户端
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        writer.StartObject();
        writer.Key("code");
        writer.Int(resultCode);
        writer.EndObject();
        cout << "Content-type: application/json\r\n\r\n";
        cout << sb.GetString() << endl;
    }
};

int main()
{
    UploadCGIApplication app;
    return app.run();
}

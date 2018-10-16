#include "TokenHelper.h"
#include <Base64Codec.h>
#include <MD5Maker.h>
#include <sstream>
#include <ConfigHelper.h>
#include <vector>
#include <hiredis.h>
#include "MakeLog.h"
//#define LOG_MODULE "TokenHelper"
//#define LOG_PROC "Test"
using namespace std;
namespace itcast
{
    string TokenHelper::GenerateToken()
    {
        //产生token的算法 时间戳+随机数生成的md5
        //产生4个1000以内的随机数
        int rand_num[4]={0};
        int i = 0;

        //设置随机种子
        srand((unsigned int)time(NULL));
        for(i = 0; i < 4; ++i)
        {
            rand_num[i] = rand()%1000;//随机数
        }

        time_t timestamp = time(nullptr);
        localtime(&timestamp);

        std::stringstream ss;
        ss<<timestamp<<'_'<<rand_num[0]<<'_'<<rand_num[1]<<'_'<<rand_num[2]<<'_'<<rand_num[3];
        string content = ss.str();

        //to base64
        auto base64String = Base64Codec::encode(vector<char>(content.begin(),content.end())); //base64编码
        //最后算出一个md5作为token的值
        //to md5
        MD5Maker md5(reinterpret_cast<const uchar*>(base64String.c_str()),base64String.length());

        string md5Str = md5.getDigestHexString();
        return md5Str;
    }
    string TokenHelper::WriteInfoToRedis(const LoginInfo &info) 
    {
        std::string errStr;
        std::string token;
        redisContext *conn=nullptr;
        do
        {
            //1 产生token
            token = GenerateToken();
            std::string key = "token_"+token;
            //2 读取配置连接redis
            string redisHost = ConfigHelper::getInstance().getVal("redis","ip");
            string redisPort = ConfigHelper::getInstance().getVal("redis","port");
            conn = redisConnect(redisHost.c_str(), stoll(redisPort));
            if(!conn||conn->err)
            {
                if (conn) {
                    errStr = std::string("Connect error:")+conn->errstr;
                } else {
                    errStr = "Connection error: can't allocate redis context\n";
                }
                break;
            }
            //3 执行命令
            redisReply *ptrRep = (redisReply*)redisCommand(conn,"hmset %s id %ld name %s nickName %s phone %s email %s",
                    key.c_str(),
                    info.id,
                    info.userName.c_str(),
                    info.nickName.c_str(),
                    info.phone.c_str(),
                    info.email.c_str()
                    );
            //4 结果集处理
            if(!ptrRep)
            {
                errStr = "Cannot get reply obj";
                break;
            }
            if(ptrRep->type!=REDIS_REPLY_STATUS||string("OK")!=ptrRep->str)
            {
                errStr = "hmset command fail";
                break;
            }
        }
        while(0);
        //5 清理工作
        if(conn)
            redisFree(conn);
        if(!errStr.empty())
        {
            throw runtime_error(errStr);
        }
        return token;
    }

    bool TokenHelper::VerifyToken(std::string token,LoginInfo &info)
    {
        //1 连接redis
        string redisHost = ConfigHelper::getInstance().getVal("redis","ip");
        string redisPort = ConfigHelper::getInstance().getVal("redis","port");
        redisContext *conn = redisConnect(redisHost.c_str(), stoll(redisPort));
        //2 查询token的key
        string key = "token_"+token;
        redisReply *ptrRep = (redisReply*)redisCommand(conn,"hmget %s id name nickName phone email",
                ("token_"+token).c_str()
                );
        //4 结果集处理
        if(!ptrRep)
        {
            redisFree(conn);
            throw runtime_error("Cannot get reply obj");
        }
        if(ptrRep->type!=REDIS_REPLY_ARRAY||ptrRep->elements!=5)
        {
            redisFree(conn);
            throw runtime_error("hmget command fail");
        }
        //获取id
        redisReply *repId = ptrRep->element[0];
        info.id = atol(repId->str);
        //获取name
        redisReply *repName = ptrRep->element[0];
        info.userName = repName->str;
        //获取nickName
        redisReply *repNickName = ptrRep->element[0];
        info.nickName = repNickName->str;
        //获取phone
        redisReply *repPhone = ptrRep->element[0];
        info.phone = repPhone->str;
        //获取email
        redisReply *repEmail = ptrRep->element[0];
        info.email = repEmail->str;

        //5 清理工作
        redisFree(conn);
        return true;
    }
}

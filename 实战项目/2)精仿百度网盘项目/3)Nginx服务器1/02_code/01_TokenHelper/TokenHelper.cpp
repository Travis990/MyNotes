#include "TokenHelper.h"
#include <hiredis.h>
#include <cstdlib>
#include <iostream>
#define REDIS_HOST "127.0.0.1"
#define REDIS_PORT 6379
using namespace std;
namespace itcast
{
    void TokenHelper::WriteInfoToRedis(std::string token , const LoginInfo &info) 
        throw(std::runtime_error)
    {
        redisContext *c;
        redisReply *reply;

        //1 建立连接
        c = redisConnect(REDIS_HOST, REDIS_PORT);
        if (c == NULL || c->err) {
            if (c) {
                redisFree(c);
                throw runtime_error( string("Connection error: ")+ c->errstr);
            } else {
                throw runtime_error(
                        "Connection error: can't allocate redis context\n");
            }
        }

        //命令执行以及返回结果的查看
        //struct LoginInfo
        //{
        //    std::string userName;
        //    std::string passwd;
        //    std::string nickName;
        //    std::string phone;
        //    std::string email;
        //    long long id;
        //};
        reply = (redisReply*)redisCommand(c,
                "HMSET %s id %ld userName %s nickName %s passwd %s phone %s email %s",
                token.c_str(),
                info.id,
                info.userName.c_str(),
                info.nickName.c_str(),
                info.passwd.c_str(),
                info.phone.c_str(),
                info.email.c_str()
                );
        if(reply==NULL||reply->type!=REDIS_REPLY_STATUS
                ||string("OK")!=reply->str)
        {
            //报错
            if(reply)
                freeReplyObject(reply);
            redisFree(c);
            throw runtime_error("HMSET fail");
        }
        freeReplyObject(reply);

        //设置超时时间
        reply = (redisReply*)redisCommand(c,"expire %s %ld",
                token.c_str(),
                24*60*60);
        if(reply==NULL||reply->type!=REDIS_REPLY_INTEGER
                ||reply->integer!=1)
        {
            //报错
            if(reply)
                freeReplyObject(reply);
            redisFree(c);
            throw runtime_error("expire fail");
        }
        freeReplyObject(reply);
        
        //清理工作
        /* Disconnects and frees the context */
        redisFree(c);
    }

    bool TokenHelper::VerifyToken(const std::string token,LoginInfo &info) 
        throw(std::runtime_error)
    {
        redisContext *c;
        redisReply *reply;

        //1 建立连接
        c = redisConnect(REDIS_HOST, REDIS_PORT);
        if (c == NULL || c->err) {
            if (c) {
                redisFree(c);
                throw runtime_error( string("Connection error: ")+ c->errstr);
            } else {
                throw runtime_error(
                        "Connection error: can't allocate redis context\n");
            }
        }

        //命令执行以及返回结果的查看
        reply = (redisReply*)redisCommand(c,
                "HMGET %s id userName nickName passwd phone email", token.c_str());
        //reply 类型不为array，就是错误处理
        if(reply==NULL||reply->type!=REDIS_REPLY_ARRAY)
        {
            //报错
            if(reply)
                freeReplyObject(reply);
            redisFree(c);
            throw runtime_error("Error in execute hmget");
        }
        
        //因为hmget对于key不存在的情况下
        //数组中所有成员都是nil，要批量判断
        size_t i;
        int tokenNotExist=1;
        for(i=0;i<reply->elements;++i)
        {
            if(reply->element[i]->type!=REDIS_REPLY_NIL)
            {
                tokenNotExist = 0;
                break;
            }
        }
        if(tokenNotExist)
        {
            //报错
            if(reply)
                freeReplyObject(reply);
            redisFree(c);
            return false;
        }
        //解析出数组里边每一个值
        info.id = atol(reply->element[0]->str);
        info.userName = reply->element[1]->str;
        info.nickName = reply->element[2]->str;
        info.passwd = reply->element[3]->str;
        info.phone = reply->element[4]->str;
        info.email = reply->element[5]->str;

        freeReplyObject(reply);

        //清理工作
        /* Disconnects and frees the context */
        redisFree(c);
        return true;
    }
}

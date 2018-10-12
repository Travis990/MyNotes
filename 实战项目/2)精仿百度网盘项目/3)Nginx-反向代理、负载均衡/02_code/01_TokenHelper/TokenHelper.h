#pragma once
#include <string>
#include <exception>
#include <stdexcept>
namespace itcast
{
    class TokenHelper
    {
    public:
        //用户信息
        struct LoginInfo
        {
            std::string userName;
            std::string passwd;
            std::string nickName;
            std::string phone;
            std::string email;
            long long id;
        };
        //使用以下方法来存储信息到redis,设定超时时间24小时分钟
        //token为key
        //info 为要存入的信息
        static void WriteInfoToRedis(std::string token , const LoginInfo &info) 
            throw(std::runtime_error);

        //使用以下方法来验证token信息,如果验证通过返回true,同时info被赋值,否则返
        //回false
        //token 为key
        //info 为要传出的信息
        static bool VerifyToken(const std::string token,LoginInfo &info) 
            throw(std::runtime_error);
    };
}

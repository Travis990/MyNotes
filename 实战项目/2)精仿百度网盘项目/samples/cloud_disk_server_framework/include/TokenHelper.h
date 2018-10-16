#pragma once
#include <string>
#include <exception>
namespace itcast
{
class TokenHelper
{
public:
    struct LoginInfo
    {
        std::string userName;
        std::string passwd;
        std::string nickName;
        std::string phone;
        std::string email;
        long long id;
    };
    //单纯的产生一个token格式的字符串
    static std::string GenerateToken();
    //使用以下方法来存储信息到redis,设定超时时间24小时分钟,返回token字符串
    static std::string WriteInfoToRedis(const LoginInfo &info);
    //使用以下方法来验证token信息,如果验证通过返回true,同时info被赋值,否则返回false
    static bool VerifyToken(const std::string token,LoginInfo &info);
};
}

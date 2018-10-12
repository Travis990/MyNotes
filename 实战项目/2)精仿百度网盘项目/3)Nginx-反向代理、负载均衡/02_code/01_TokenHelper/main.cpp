#include "TokenHelper.h"

#include <iostream>
using namespace std;
using namespace itcast;

int main()
{
    //构造一个用户的信息
    TokenHelper::LoginInfo info,info2;
    info.id =10000;
    info.userName = "itcast_user_name";
    info.nickName = "itcast_nick_name";
    info.passwd = "123456";
    info.phone = "1111111111";
    info.email = "itcast@itcast.cn";

    //调用 存储到redis的函数
    try
    {
        TokenHelper::WriteInfoToRedis("token_test",info);
        bool ret = TokenHelper::VerifyToken("token_test",info2);
        if(ret)
        {
            cout<<"Get token_test info:"<<endl;
            cout<<"id:\t"<<info.id<<endl;
            cout<<"userName:\t"<<info.userName<<endl;
            cout<<"nickName:\t"<<info.nickName<<endl;
            cout<<"passwd:\t"<<info.passwd<<endl;
            cout<<"phone:\t"<<info.phone<<endl;
            cout<<"email:\t"<<info.email<<endl;
        }
        else
        {
            cerr<<"Key token_test not exists"<<endl;
        }
    }
    catch(const exception &e)
    {
        cerr<<"Get exception : "<<e.what()<<endl;
    }
}

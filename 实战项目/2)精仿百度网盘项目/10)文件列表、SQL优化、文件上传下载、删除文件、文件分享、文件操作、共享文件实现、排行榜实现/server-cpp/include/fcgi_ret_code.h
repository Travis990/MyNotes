#ifndef FCGI_RET_CODE_H
#define FCGI_RET_CODE_H


//common
//通用的成功和错误的返回码
#define RET_CODE_OK 0
#define RET_CODE_ERROR 1

//user
//用户已存在
#define RET_CODE_USER_EXISTS 11
//用户没登录，找不到token
#define RET_CODE_USER_NOT_LOGIN 12
//验证失败，用户密码不正确
#define RET_CODE_USER_VERIFY_FAIL 13

//file
#define RET_CODE_FILE_ERROR 20
//文件已经存在 
#define RET_CODE_FILE_EXISTS 21
//文件不存在
#define RET_CODE_FILE_NOT_EXISTS 22


#endif

#pragma once
#include <cstddef>
#include <string>
#include <array>
#include <md5.h>
//依赖fastdfs 的libfastcommon写的一个MD5计算工具
namespace itcast
{
    typedef unsigned char uchar;
    class MD5Maker
    {
    public:
        MD5Maker(const uchar *data , size_t len);
        std::array<uchar,16> getDigest()const;
        std::string getDigestHexString()const;
    private:
        MD5_CTX mCtx;
    };
}

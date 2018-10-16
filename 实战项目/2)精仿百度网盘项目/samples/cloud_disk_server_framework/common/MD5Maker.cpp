#include "MD5Maker.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <md5.h>
namespace itcast{
    MD5Maker::MD5Maker(const uchar *data , size_t len)
    {
        my_md5_init(&this->mCtx);
        my_md5_update(&this->mCtx,const_cast<uchar*>(data),static_cast<unsigned int>(len));
    }
    std::array<uchar,16> MD5Maker::getDigest()const
    {
        unsigned char arr[16]={0};
        my_md5_final(arr,const_cast<MD5_CTX*>(&this->mCtx));
        std::array<uchar,16> ret;
        for(size_t i = 0 ; i< 16;++i)
        {
            ret[i] = arr[i];
        }
        return ret;
    }
    std::string MD5Maker::getDigestHexString()const
    {
        unsigned char arr[16]={0};
        my_md5_final(arr,const_cast<MD5_CTX*>(&this->mCtx));
        std::stringstream ss;
        for(int i = 0 ; i< 16;++i)
        {
            int tm = arr[i];
            ss<<std::hex<<std::setw(2)<<std::setfill('0')<<tm;
        }
        return ss.str();
    }
}

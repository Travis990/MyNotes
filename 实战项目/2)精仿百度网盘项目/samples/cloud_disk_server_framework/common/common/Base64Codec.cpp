#include "Base64Codec.h"
#include <cmath>
#include <cstring>
namespace itcast
{
    static const char *base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string Base64Codec::encode(std::vector<char>bindata)
    {
        unsigned char current;
        std::string base64;
        base64.resize(size_t(ceil(bindata.size()*1.0/3))*4);

        size_t i,j;
        for (i = 0, j = 0 ; i < bindata.size() ; i += 3 )
        {
            current = static_cast<unsigned char>(bindata[i] >> 2) ;
            current &= (unsigned char)0x3F;
            base64[j++] = base64char[current];

            current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;
            if ( i + 1 >= bindata.size() )
            {
                base64[j++] = base64char[(int)current];
                base64[j++] = '=';
                base64[j++] = '=';
                break;
            }
            current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F );
            base64[j++] = base64char[(int)current];

            current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;
            if ( i + 2 >= bindata.size() )
            {
                base64[j++] = base64char[(int)current];
                base64[j++] = '=';
                break;
            }
            current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 );
            base64[j++] = base64char[(int)current];

            current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;
            base64[j++] = base64char[(int)current];
        }
        base64[j] = '\0';
        return base64;
    }

    std::vector<char> Base64Codec::decode(std::string base64)
    {
        size_t i, j;
        unsigned char k;
        std::vector<char> bindata;
        bindata.resize(base64.length()*3/4);
        unsigned char temp[4];
        for ( i = 0, j = 0; i<base64.length() ; i += 4 )
        {
            memset( temp, 0xFF, sizeof(temp) );
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64char[k] == base64[i] )
                    temp[0]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64char[k] == base64[i+1] )
                    temp[1]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64char[k] == base64[i+2] )
                    temp[2]= k;
            }
            for ( k = 0 ; k < 64 ; k ++ )
            {
                if ( base64char[k] == base64[i+3] )
                    temp[3]= k;
            }

            bindata[j++] = ((char)(((unsigned char)(temp[0] << 2))&0xFC)) |
                ((char)((unsigned char)(temp[1]>>4)&0x03));
            if ( base64[i+2] == '=' )
                break;

            bindata[j++] = ((char)(((unsigned char)(temp[1] << 4))&0xF0)) |
                ((char)((unsigned char)(temp[2]>>2)&0x0F));
            if ( base64[i+3] == '=' )
                break;

            bindata[j++] = ((char)(((unsigned char)(temp[2] << 6))&0xF0)) |
                ((char)(temp[3]&0x3F));
        }
        bindata.resize(j);
        return bindata;
    }
}

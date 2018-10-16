#pragma once
#include <string>
#include <vector>


namespace itcast
{
class Base64Codec
{
public:
    static std::string encode(std::vector<char>bindata);
    static std::vector<char> decode(std::string base64);
};
}

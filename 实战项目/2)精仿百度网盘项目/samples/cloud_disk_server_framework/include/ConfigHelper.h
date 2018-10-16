#pragma once
#include <string>
#include <map>
#include <string>
namespace itcast
{
    class ConfigHelper
    {
    public:
        static ConfigHelper &getInstance(){return smInstance;};
        std::string getVal(std::string field,std::string key);
    private:
        ConfigHelper();
        ConfigHelper(const ConfigHelper&);
        static ConfigHelper smInstance;
        std::map<std::string,std::map<std::string,std::string>> mCfgRootMap;
    };
}

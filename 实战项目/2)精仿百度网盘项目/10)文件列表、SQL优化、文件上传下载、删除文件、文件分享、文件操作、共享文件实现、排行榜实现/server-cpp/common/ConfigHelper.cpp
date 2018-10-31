#include "ConfigHelper.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;
using namespace std;
namespace itcast
{
    ConfigHelper ConfigHelper::smInstance;
    ConfigHelper::ConfigHelper()
    {
        ifstream ifs;
        ifs.open("./conf/cfg.json");
        if(!ifs.is_open())
        {
            throw runtime_error("Can not open file ./conf/cfg.json");
        }
        string content;
        for(int read_sum = 0 ; !ifs.eof();)
        {
            char buf[1024];
            ifs.read(buf,sizeof(buf)-1);
            read_sum+=ifs.gcount();
            buf[ifs.gcount()]='\0';
            content+=buf;
        }
        Document d;
        d.Parse(content.c_str());
        map<string, map<string,string>> cfgRootMap;
        auto root = d.GetObject();
        for(auto it = root.begin(); it != root.end();++it)
        {
            map<string,string> childMap;
            auto obj = it->value.GetObject();
            for (auto itChild = obj.begin() ; itChild!=obj.end();++itChild)
            {
                childMap.insert(make_pair(itChild->name.GetString(),itChild->value.GetString()));
            }
            cfgRootMap.insert(make_pair(it->name.GetString(),childMap));
        }
        this->mCfgRootMap.swap(cfgRootMap);
    }
    string ConfigHelper::getVal(string field,string key)
    {
        return this->mCfgRootMap[field][key];
    }
}

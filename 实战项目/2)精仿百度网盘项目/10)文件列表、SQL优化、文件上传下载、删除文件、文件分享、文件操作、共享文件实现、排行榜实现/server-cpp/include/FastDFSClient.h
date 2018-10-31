#pragma once
#include <string>
#include <stdexcept>
using namespace std;
namespace itcast
{
class FastDFSClient
{
public:
    explicit FastDFSClient(string cfgFile);
    string upload(string file) throw(runtime_error);
private:
    string mCfgFile;
};
}

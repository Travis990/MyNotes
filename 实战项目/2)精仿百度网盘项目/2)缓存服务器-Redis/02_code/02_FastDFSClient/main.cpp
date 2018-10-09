#include "FastDFSClient.h"
#include <iostream>
#include <string>
using namespace std;
using namespace itcast;
int main()
{
    string confFile = "/etc/fdfs/client.conf2";
    string localFile = "./main.cpp";
    //声明一个对象
    FastDFSClient client(confFile); 
    try
    {
        string fileId = client.upload(localFile);
        cout<<"Get File Id is "<< fileId<<endl;
    }
    catch(const exception &e)
    {
        cerr<<"Get exception : "<<e.what()<<endl;
    }
}

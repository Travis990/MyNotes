#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <iostream>
#include <string>

using namespace rapidjson;
using namespace std;

//解析json
int parseJsonString()
{
    Document document;
    string json= "{\"name\":\"itcast\",\"age\":18}";
    if (document.Parse(json.c_str()).HasParseError())
    {
        cerr<<"Parse Error posistion:"<<document.GetErrorOffset()<<" error reason:"
            <<GetParseError_En(document.GetParseError())<<endl;
        return 1;
    }
    cout<<"name is " << document["name"].GetString()<<endl;
    cout<<"age is " << document["age"].GetInt()<<endl;
    return 0;
}

//序列化为json字符串
void writeJsonString()
{
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    
    writer.StartObject();               // Between StartObject()/EndObject(), 
    writer.Key("hello");                // output a key,
    writer.String("world");             // follow by a value.
    writer.Key("t");
    writer.Bool(true);
    writer.Key("f");
    writer.Bool(false);
    writer.Key("n");
    writer.Null();
    writer.Key("i");
    writer.Uint(123);
    writer.Key("pi");
    writer.Double(3.1416);
    writer.Key("a");
    writer.StartArray();                // Between StartArray()/EndArray(),
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);                 // all values are elements of the array.
    writer.EndArray();
    writer.EndObject();

    // {"hello":"world","t":true,"f":false,"n":null,"i":123,"pi":3.1416,"a":[0,1,2,3]}
    cout << s.GetString() << endl;
}

int main() 
{
    parseJsonString();
    writeJsonString();
    return 0;
}

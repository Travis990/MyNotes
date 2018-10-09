#include <stdexcept>
#include <iostream>

using namespace std;
void testFunc() throw(runtime_error)
{
    throw runtime_error("这是错误信息");
}

int main()
{
    try
    {
        testFunc();
    }
    catch(const exception &e)
    {
        cerr<<"Get exception "<<e.what()<<endl;
    }
    return 0;
}


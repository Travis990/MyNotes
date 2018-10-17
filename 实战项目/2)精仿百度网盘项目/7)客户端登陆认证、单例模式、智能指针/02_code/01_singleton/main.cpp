#include <thread>
#include <mutex>
#include <iostream>
#define THREAD_NUM 10
using namespace std;

class Singleton
{
public:
    //清理工人
    class Garbo
    {
    public:
        ~Garbo()
        {
            if(smInstance)
            {
                delete smInstance;
            }
        }
    };
    static Singleton *getInstance()
    {
        //双重判定
        if(smInstance==nullptr)
        {
            //smInstanceMutex.lock();
            lock_guard<mutex> guard(smInstanceMutex);
            if(smInstance==nullptr)
            {
                smInstance = new Singleton;
                throw 1; 
            }
            //smInstanceMutex.unlock(); //如果因为异常这句没执行会死锁
        }
        return smInstance;
    }
private:
    Singleton()
    {
        //默认构造函数
        cout<<"Singleton construction"<<endl;
    }
    ~Singleton()
    {
        cout<<"Singleton destruction"<<endl;
    }

    static Singleton *smInstance;
    static mutex smInstanceMutex;
    static Garbo smGarbo;
};


//静态成员变量需要在类外进行定义
Singleton *Singleton::smInstance = nullptr;
mutex Singleton::smInstanceMutex;
Singleton::Garbo Singleton::smGarbo;


void testFunc(int num)
{
    //cout<<num<<endl;
    try
    {
        Singleton::getInstance();
    }
    catch(...)
    {
    }
}

int main()
{
    thread *arr[THREAD_NUM]={nullptr}; 
    for(int i=0;i<THREAD_NUM;++i)
    {
        //创建线程
        //arr[i]= new thread([](int num){cout<<num<<endl;}, i);
        arr[i]= new thread(testFunc, i);
    }
    for(int i=0;i<THREAD_NUM;++i)
    {
        //等待所有线程结束才返回
        arr[i]->join();
    }
    for(int i=0;i<THREAD_NUM;++i)
    {
        delete arr[i];
    }
    return 0;
}

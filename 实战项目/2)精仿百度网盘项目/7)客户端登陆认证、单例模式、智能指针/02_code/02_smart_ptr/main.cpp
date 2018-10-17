
#include <iostream>
#include <memory>
using namespace std;

class Person
{
public:
    Person()
    {
        cout<<"Person construction"<<endl;
    }
    void doSth()
    {
        cout<<"Person dosth"<<endl;
    }
    ~Person()
    {
        cout<<"Person Destruction"<<endl;
    }
};

void uniq_ptr_test()
{
    try
    {
        unique_ptr<Person> p(new Person);

        //智能指针都重写了 ->操作符
        p->doSth();

        //再次赋值，使用reset，先自动释放之前的对象，然后再赋值过来
        p.reset(new Person);



        //要么不要复制，要么就用移动
        //unique_ptr<Person> p2 = p;
        //unique_ptr<Person> p2 = move(p);

        //throw 1;
    }
    catch(...)
    {
    }
}

shared_ptr<Person> shared_ptr_test()
{
    shared_ptr<Person> p(new Person);
    return p;
}

int main()
{
    shared_ptr<Person> p = shared_ptr_test();

    cout<<"HelloWorld"<<endl;

    //new person 的生命周 已经延长到这里
    return 0;
}

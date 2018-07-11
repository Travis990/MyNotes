#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

// *面试时有可能会问到,以下这个类里有什么? 注意你看不到的!
class Dejan
{
	// - 4个函数
	// 1.默认构造函数
	// 2.默认的析构函数
	// 3.默认的拷贝构造函数(用一个已有的对象去初始化另一个对象)
	// 4.默认的运算符重载的函数(赋值函数）

	// - 1个指针
	// 函数里有一个指针 this
};

class Girl
{
public: // 注意：构造函数和析构函数必须是公有的
	// 无参构造函数 构造函数没有返回值，构造函数可以重载
	Girl()
	{
		age = 10;
		cout << "无参构造" << endl;
	}
	
	// 有参构造
	Girl(int age)
	{
		this->age = age;
		cout << "有参构造" << endl;
	}
	
	// 拷贝构造函数
	Girl(const Girl &girl) // girl是一个已有的对象
	{
		age = girl.age; // (用一个已有的对象去初始化另一个对象)
		cout << "拷贝构造函数" << endl;
	}
	
	// 析构函数，没有返回值，没有参数，不能重载
	~Girl()
	{
		cout << "析构函数" << endl;
	}
public:
	int age;
};

void test()
{
	// 用类实例化一个对象
	// 1.分配内存。2.初始化（构造函数）
	Girl girl; // 栈区

	Girl girl2(18);
	Girl girl3(girl);

	// 当对象销毁前，会进行清理工作（析构函数），然后在销毁对象
}

int main()
{
	test();

	system("pause");
	return 0;
}
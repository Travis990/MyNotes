#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<string>
using namespace std;

void ThreadFunc(string& str)
{
	cout << str << endl;
}

int main()
{
	thread t1;
	cout << t1.get_id() << endl;   // 0, 线程ID:0
	cout << t1.joinable() << endl; // 0, 不可被join()

	// 使用有参构造函数
	thread t2(ThreadFunc, string("Hello"));
	cout << t2.get_id() << endl;
	cout << t2.joinable() << endl;

	// thread对象在销毁之前必须调用join(),否则程序终止 或 使用 detach()
	//t2.join(); // 等待子线程执行完毕
	t2.detach(); // 使当前线程对象分离

	system("pause");
	return 0;
}
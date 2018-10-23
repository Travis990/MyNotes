#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<thread>
using namespace std;
// 命名空间this_thread 有的线程辅助函数: get_id() yield() sleep_for() sleep_util()
using namespace this_thread;
// 命名空间chrono 有seconds模板类、milliseconds模板类
using namespace chrono;

// thread的所有"辅助函数"都在std::this_thread命名空间中

void ThreadFun(string& str)
{
	cout << "线程ID:" << get_id() << endl; // 获取当前执行线程ID
	while (1) 
	{
		cout << str << endl;
		//sleep_for(seconds(1)); // 让线程睡眠1秒

		yield(); // 让线程睡眠一个极小的时间片, 给其他线程执行

		sleep_until(system_clock::now() + milliseconds(1000)); // 当前时间+1秒
	}
}

int main()
{
	thread t1(ThreadFun, string("Hello"));
	cout << "线程ID:"<<t1.get_id() << endl;

	// 等待子线程完成
	t1.join();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<future>
using namespace std;
using namespace this_thread;
using namespace chrono;

// 费时操作
void work_1(promise<int>& prom, int a, int b)
{
	cout << "work_1开始计算!" << endl;
	sleep_for(seconds(3));
	prom.set_value( a + b );
}

int work_2(int a, int b)
{
	cout << "work_2开始计算!" << endl;
	sleep_for(seconds(2));
	return a + b;
}

int work_3(int a, int b)
{
	cout << "work_3开始计算!" << endl;
	sleep_for(seconds(2));
	return a + b;
}

int main()
{
	// 1) promise内部包装了一个值
	promise<int> prom;
	future<int> f1 = prom.get_future(); // 使用get_future成员函数获取future
	thread(work_1, ref(prom), 1, 2).detach();
	f1.wait(); // 等待值设置
	cout << "计算结果:" << f1.get() << endl; // 获取结果


	// 2) packaged_task包装一个操作
	packaged_task<int(int, int)> task(work_2);
	future<int> f2 = task.get_future(); // 使用get_future成员函数获取future
	thread(move(task),11,22).detach();
	f2.wait(); // 等待结果
	cout << "计算结果:" << f2.get() << endl; // 获取结果


	// 3) async内部是一个线程
	future<int> f3 = async(work_3, 111, 222);
	f3.wait(); // 等待结果
	cout << "计算结果:" << f3.get() << endl; // 获取结果

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<future>
#include<thread>
using namespace std;
using namespace this_thread;
using namespace chrono;

int work(int a, int b)
{
	cout << "开始计算!" << endl;
	sleep_for(seconds(5)); // 处理费时操作
	cout << "结束计算!" << endl;
	return a + b;
}

int main()
{
	// packaged_task包装了一个可调用的目标
	packaged_task<int(int, int)> pack(work);

	future<int> result = pack.get_future(); // 获取packaged_task内部的future

	thread t1( move(pack), 123, 456);
	t1.detach();

	int sum = result.get();
	cout << "获取结果:" << sum << endl;

	system("pause");
	return 0;
}
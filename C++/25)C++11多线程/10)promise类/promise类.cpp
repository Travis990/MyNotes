#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<future>
#include<thread>
using namespace std;
using namespace this_thread;
using namespace chrono;

// 费时操作
void work_1(promise<int>& prom)
{
	cout << "开始计算!" << endl;
	sleep_for(seconds(5));
	// promise设置结果值
	cout << "计算完成!" << endl;
	prom.set_value(666); // 设置结果, future会get到
}

void work_2(promise<int>& prom)
{
	cout << "开始计算!" << endl;
	sleep_for(seconds(5));
	// promise设置结果值
	try
	{
		throw runtime_error("运行时错误!");
	}
	catch(...)
	{
		prom.set_exception(current_exception());
	}
}

void test_1()
{
	// 定义一个promise
	promise<int> prom;
	// future和promise搭配使用, 类似于async
	future<int> result = prom.get_future();

	thread t1(work_1, ref(prom));
	t1.detach();

	int sum = result.get();
	cout << "获取结果:" << sum << endl;
}

void test_2()
{
	// 定义一个promise
	promise<int> prom;
	// future和promise搭配使用, 类似于async
	future<int> result = prom.get_future();

	thread t1(work_2, ref(prom));
	t1.detach();

	try 
	{
		int sum = result.get();
		cout << "获取结果:" << sum << endl;
	}
	catch (exception& e)
	{
		cout << "结果异常" << e.what() << endl;
	}
}



int main()
{
	test_2();

	system("pause");
	return 0;
}
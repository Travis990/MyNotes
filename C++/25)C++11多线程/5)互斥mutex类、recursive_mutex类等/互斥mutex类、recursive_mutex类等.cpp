#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
using namespace this_thread;
using namespace chrono;

int tickets = 100;

// 定义一个互斥对象
mutex m; // 不可重复加锁
recursive_mutex m2; // 可以递归加锁
timed_mutex m3; // 可以指定锁住的时间

recursive_timed_mutex m4; // 以上三种的综合

void SellThread_1(string& str) 
{
	while (tickets > 0)
	{
		m.lock(); // 加锁
		if (tickets > 0)
		{
			sleep_for(milliseconds(100)); // 100毫秒
			printf("%s 卖出 %d 张票\n", str.c_str(), tickets--);
		}
		m.unlock(); // 解锁
	}
}

void SellThread_2(string& str)
{
	while (tickets > 0)
	{
		m2.lock(); // 加锁
		m2.lock(); // 再次加锁
		if (tickets > 0)
		{
			sleep_for(milliseconds(100)); // 100毫秒
			printf("%s 卖出 %d 张票\n", str.c_str(), tickets--);
		}
		m2.unlock(); // 解锁
		m2.unlock(); // 解锁
	}
}

void SellThread_3(string& str)
{
	while (tickets > 0)
	{
		m3.try_lock_for(seconds(3)); // 加锁, 锁住3秒
		if (tickets > 0)
		{
			sleep_for(milliseconds(100)); // 100毫秒
			printf("%s 卖出 %d 张票\n", str.c_str(), tickets--);
		}
		//m3.unlock(); // 解锁, 因为try_lock_for 3秒后会自动解锁所以不需要解锁
	}
}

void SellThread_4(string& str)
{
	while (tickets > 0)
	{
		m4.try_lock_for(seconds(3)); // 加锁, 锁住3秒
		m4.try_lock_for(seconds(3)); // 加锁, 锁住3秒
		if (tickets > 0)
		{
			sleep_for(milliseconds(100)); // 100毫秒
			printf("%s 卖出 %d 张票\n", str.c_str(), tickets--);
		}
		//m4.unlock(); // 解锁, 因为try_lock_for 3秒后会自动解锁所以不需要解锁
	}
}

// mutex
void test_1()
{
	thread t1(SellThread_1, string("售票窗口A:"));
	thread t2(SellThread_1, string("售票窗口B:"));

	t1.join();
	t2.join();
}

// recursive_mutex
void test_2()
{
	thread t1(SellThread_2, string("售票窗口A:"));
	thread t2(SellThread_2, string("售票窗口B:"));

	t1.join();
	t2.join();
}

// timed_mutex
void test_3()
{
	thread t1(SellThread_3, string("售票窗口A:"));
	thread t2(SellThread_3, string("售票窗口B:"));

	t1.join();
	t2.join();
}

// recursive_timed_mutex
void test_4()
{
	thread t1(SellThread_4, string("售票窗口A:"));
	thread t2(SellThread_4, string("售票窗口B:"));

	t1.join();
	t2.join();
}

int main()
{
	test_3();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<mutex>
#include<thread>
#include<stdexcept>
using namespace std;
using namespace this_thread;

mutex m;

void ThreadFunc_1()
{
	try {
		for (int i = 0; i < 10; ++i)
		{
			m.lock();
			if (i == 3) throw logic_error("发生异常!");
			cout << "A打印" << i << endl;
			m.unlock(); // 异常抛出时,导致没有unlock,使得B无法获取mutex, 死锁
			sleep_for(chrono::seconds(1));
		}
	}
	catch (logic_error& e)
	{
		cout << "错误" << e.what() << endl;
	}
	
}

void ThreadFunc_2()
{
	for (int i = 0; i < 10; ++i)
	{
		m.lock();
		cout << "B打印" << i << endl;
		m.unlock();
		sleep_for(chrono::seconds(1));
	}
}

void ThreadFunc_3()
{
	try {
		for (int i = 0; i < 10; ++i)
		{
			{
				lock_guard<mutex> lk(m);
				if (i == 3) throw logic_error("发生异常!");
				cout << "A打印" << i << endl;
			}
			sleep_for(chrono::seconds(1));
		}
	}
	catch (logic_error& e)
	{
		cout << "错误" << e.what() << endl;
	}

}

void test_1()
{
	thread t1(ThreadFunc_1);
	thread t2(ThreadFunc_2);

	t1.join();
	t2.join();
}

void test_2()
{
	thread t1(ThreadFunc_3);
	thread t2(ThreadFunc_2);

	t1.join();
	t2.join();
}

int main()
{
	test_2();

	system("pause");
	return 0;
}
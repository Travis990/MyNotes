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
			// unique_lock使用更加灵活, 与 lock_guard区别就是 可以自主 lock()、unlock()
			unique_lock<mutex> lk(m); // unique_lock 会自动上锁、自动解锁, 当然也可以 自主 上锁&解锁来控制作用域
			if (i == 3) throw logic_error("发生异常!");
			cout << "A打印" << i << endl;
			lk.unlock();
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



void test()
{
	thread t1(ThreadFunc_1);
	thread t2(ThreadFunc_2);

	t1.join();
	t2.join();
}

int main()
{
	test();

	system("pause");
	return 0;
}
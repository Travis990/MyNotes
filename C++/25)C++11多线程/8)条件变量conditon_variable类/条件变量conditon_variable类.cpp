#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<mutex>
#include<condition_variable>
using namespace std;
using namespace this_thread;
using namespace chrono;

condition_variable cv; // 仅支持unique_lock<mutex>作为wait()的参数
condition_variable_any cv2; // 接受任何lockable作为wait()的参数
mutex m;

void ThreadFunc_1(int id)
{
	unique_lock<mutex> lc(m);
	cv.wait(lc); // 等待被唤醒

	cout << "线程ID:" << id << "执行!" << endl;
}

void ThreadFunc_2(int id)
{
	unique_lock<mutex> lc(m);
	cv2.wait(lc);

	cout << "线程ID:" << id << "执行!" << endl;
}

void test_1()
{
	thread t1(ThreadFunc_1, 1);
	thread t2(ThreadFunc_1, 2);
	thread t3(ThreadFunc_1, 3);

	cout << "3秒后唤醒: " << endl;
	sleep_for(seconds(3)); // 3秒之后唤醒所有线程

	//cv.notify_all(); // 唤醒所有

	cv.notify_one(); // 只唤醒一个
	cv.notify_one();

	t1.join();
	t2.join();
	t3.join();
}

void test_2()
{
	thread t1(ThreadFunc_2, 1);
	thread t2(ThreadFunc_2, 2);
	thread t3(ThreadFunc_2, 3);

	cout << "3秒后唤醒: " << endl;
	sleep_for(seconds(3)); // 3秒之后唤醒所有线程

	cv2.notify_all();

	t1.join();
	t2.join();
	t3.join();
}

int main()
{
	test_2();

	system("pause");
	return 0;
}
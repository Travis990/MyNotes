#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<atomic> // 原子头操作文件
using namespace std;

atomic<int> N = 0; // 使用atomic可以保证对N操作的原子性

void ThreadFunc()
{
	for ( int i = 0; i < 1000000; ++i )
	{
		++N; // 线程并发导致 加操作 重叠 不是原子操作, 因此有可能小于 2000000
	}
}

int main()
{
	thread t1(ThreadFunc);
	thread t2(ThreadFunc);

	t1.join();
	t2.join();

	cout << N << endl; // 应该是2000000

	system("pause");
	return 0;
}
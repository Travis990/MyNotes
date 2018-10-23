#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<future>
#include<thread>
using namespace std;
using namespace this_thread;
using namespace chrono;

// 费时的操作
int work(int a, int b)
{
	cout << "开始计算:" << endl;
	sleep_for(seconds(5)); // 这是计算耗时5秒
	return a + b;
}

int main()
{
	future<int> result = async(work, 123, 456); // move赋值操作

	result.wait(); // 等待结果算出, 算出后才会继续执行
	cout << "算出结果:" << endl;
	int sum = result.get(); // 获取结果
	cout << "最终的结果是:" << sum << endl;

	system("pause");
	return 0;
}
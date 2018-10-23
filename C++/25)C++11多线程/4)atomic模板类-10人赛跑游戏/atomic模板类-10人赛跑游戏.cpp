#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<atomic>
#include<vector>
using namespace std;
using namespace this_thread;

atomic<bool> ready = false; // 是否抢响

atomic_flag win = ATOMIC_FLAG_INIT; // 终点线

void Run(int id)
{
	// 枪没响, 不能跑
	while (!ready)
	{
		yield(); // 让其他线程先执行
	}

	// 表示跑的过程
	for (int i = 0; i < 100000; ++i){}

	// 如果没有被设置过, 返回false
	if (!win.test_and_set()) // 调用一次后, 下次调用返回true
	{
		cout << id << "号选手赢得第一名!"<<endl;
	}
}

int main()
{
	// 10个选手赛跑
	vector<thread> vecPlayers;
	for (int i=0;i<=10;++i)
	{
		vecPlayers.push_back(thread(Run, i));
	}
	cout << "10个选手已准备好!" << endl;

	// 准备发命令: 预备跑
	sleep_for(chrono::seconds(3));
	cout << "3、2、1 预备.. 跑!" << endl;

	ready = true;

	// 等待所有选手跑完
	for (thread& t:vecPlayers) 
	{
		t.join();
	}

	system("pause");
	return 0;
}
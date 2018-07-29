#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<list>
#include<string>
#include<ctime>
#include<vector>
using namespace std;

//需求:人员乘坐电梯（插入和删除频率高）
//人员排队进入电梯，获取电梯搭乘人员的人次

// 抽象人员
class Student
{
public:
	string name;
};

// 创建人员
void setStudent(queue<Student> &que, int num)
{
	string setName = "ABCDEFGHIJK";
	int sum = rand() % 10;
	for (int i = 0; i < sum; i++)
	{
		Student stu;

		char buf[64] = { 0 };
		sprintf(buf, "%d", num);
		string s(buf); // 转换类型
		stu.name = "第";
		stu.name += s;
		stu.name += "层";
		stu.name += setName[i]; // 第1层A

		que.push(stu); // 把人员放入容器
	}
}

// mylist是电梯 que是要进入电梯的人员 Vpush是存储进电梯的人员
int Pushlist(list<Student> &mylist, queue<Student> &que, vector<Student> &Vpush)
{
	int pushnum = 0;//记录每层进入电梯的人员次数

	while (!que.empty()) //判断每层是否有人排队进入电梯
	{
		if (mylist.size() >= 15)
		{
			break;
		}

		Student s = que.front();//获取元素
		Vpush.push_back(s);//把进入电梯的人员存储到vector容器中

		mylist.push_back(s);//人员进入电梯

		que.pop();//移除队头人员

		pushnum++;
	}

	return pushnum;
}

// 出电梯
int Poplist(list<Student> &mylist, vector<Student> &Vpop, int pos)
{
	int popnum = 0;

	if (pos == 17) // 当电梯在17层时，所有的人都出电梯
	{
		while (!mylist.empty()) //判断电梯是否有人
		{
			Student s = mylist.front();
			Vpop.push_back(s); // 记录出电梯的人员

			mylist.pop_front(); // 人员出电梯

			popnum++;
		}
	}

	int num = rand() % 5;
	if (num == 0) // 表示没人出电梯
	{
		return popnum;
	}

	// 当电梯有人时，且人数大于等于出电梯的人数
	if (mylist.size() > 0 && mylist.size() >= num)
	{
		for (int i = 0; i < num; i++)
		{
			Student s = mylist.front();
			Vpop.push_back(s); //记录出电梯的人员

			mylist.pop_front(); //人员出电梯
			popnum++;
		}
	}

	return popnum;
}

void printVector(vector<Student> &vec)
{
	for (vector<Student>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << (*it).name << endl;
	}
	cout << endl;
}

void test()
{
	//随机种子
	srand((unsigned int)time(NULL));
	//创建电梯
	list<Student> mylist;

	//记录进入电梯的总人数
	int PushNum = 0;
	//记录出电梯的总人数
	int PopNum = 0;
	//存储进入电梯的人员
	vector<Student> Vpush;
	//存储出电梯的人员
	vector<Student> Vpop;

	for (int i = 0; i < 18; i++) // 电梯上升
	{
		//创建人员
		queue<Student> que;
		setStudent(que, i);

		//电梯最多能坐15人
		if (mylist.size() <= 15)
		{
			//进入电梯事件到17层就结束，所有17层不需要进入电梯
			if (i < 17)
			{
				//进电梯，需要记录进电梯的人员总数，可以通过返回值来获取
				//记录进电梯的人员姓名，可以把人员放入容器
				PushNum += Pushlist(mylist, que, Vpush);
			}
		}

		//当电梯有人才能出电梯
		if (mylist.size() > 0)
		{
			if (i > 1) //第一层没有人出电梯
			{
				//出电梯
				PopNum += Poplist(mylist, Vpop, i);
			}
		}
	}

	//打印出电梯的人员姓名
	printVector(Vpush);

	//打印进电梯的人员姓名
	printVector(Vpop);

	cout << "进电梯人次:" << PushNum << " 出电梯人次:" << PopNum << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
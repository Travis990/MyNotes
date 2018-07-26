#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<ctime>
#include<algorithm> // 算法头文件
using namespace std;

// 5个学生，10个评委，去掉最高分，最低分，取平均分

// 抽象学生
class Student
{
public:
	string name;
	int mscore;
};

// 创建学生，把学生放到vector
void createStudent(vector<Student> &vec)
{
	string Setname = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		// 创建学生
		Student s;
		s.name = "学生";
		s.name += Setname[i];
		s.mscore = 0;
		vec.push_back(s); // 把学生放入容器
	}
}

// 对每个学生进行打分，分数放入deque容器中
void SetScore(vector<Student> &vec)
{
	// 随机种子
	srand((unsigned int)time(NULL));
	// 遍历学生
	for (vector<Student>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		// 分数保存deque
		deque<int> dScore;
		for (int i = 0; i < 10; i++)
		{
			// 10个评委给学生打分
			int score = rand() % 70 + 30; // 随机分数
			dScore.push_back(score); // 把分数放入容器
		}
		// 排序
		sort(dScore.begin(), dScore.end());

		// 去掉最高和最低分
		dScore.pop_back();
		dScore.pop_front();

		// 求总分
		int num = 0;
		for (deque<int>::iterator dit = dScore.begin(); dit != dScore.end(); ++dit)
		{
			num += (*dit);
		}

		// 求平均分
		int ageSore = num / dScore.size();

		// 保存平均分
		it->mscore = ageSore;
	}
}

bool mycompare(Student &s1, Student &s2)
{
	return s1.mscore > s2.mscore;
}

void ShowStudentScore(vector<Student> &vec)
{
	// 排序
	sort(vec.begin(), vec.end(), mycompare);
	for (vector<Student>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << "Name:" << it->name << " Score:" << it->mscore << endl;
	}
}

void test()
{
	vector<Student> vstu;
	// 1.创建学生
	createStudent(vstu);
	// 2.评委给学生打分
	SetScore(vstu);
	// 3.根据学生成绩排名
	ShowStudentScore(vstu);
}

int main()
{
	test();

	system("pause");
	return 0;
}
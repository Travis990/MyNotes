#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Cube 
{
public:
	void init()
	{
		mL = 0;
		mW = 0;
		mH = 0;
	}
	void setL(int l)
	{
		mL = l;
	}
	int getL()
	{
		return mL;
	}
	void setW(int w)
	{
		mW = w;
	}
	int getW()
	{
		return mW;
	}
	void setH(int h)
	{
		mH = h;
	}
	int getH()
	{
		return mH;
	}

	// 求立方体的面积
	int caculaS()
	{
		return 2 * mL * mW + 2 * mL * mH + 2 * mW * mH;
	}

	// 求立方体的体积
	int caculaV()
	{
		return mL*mW*mH;
	}
	// 成员函数来判断
	// 判断两个立方体是否相等（如果长宽高都相等，就认为两个立方体相等）
	bool compareCube(Cube c1)
	{
		if (getH() == c1.getH() && getW() == c1.getW() && getL() == c1.getL())
		{
			return true;
		}
		return false;
	}
private:
	int mL;
	int mW;
	int mH;
};

// 全局函数判断
bool MycompareCube(Cube c1, Cube c2)
{
	if (c2.getH() == c1.getH() && c2.getW() == c1.getW() && c2.getL() == c1.getL())
	{
		return true;
	}
	return false;
}

int main()
{
	// 1.分配空间，2.初始化工作
	Cube m1;
	m1.init();
	Cube m2;
	m2.init();

	m1.setH(10);
	m1.setL(10);
	m1.setW(10);

	m2.setH(10);
	m2.setL(10);
	m2.setW(10);

	bool ret = m1.compareCube(m2);
	if (ret)
	{
		cout << "两个立方体相等" << endl;
	}
	else
	{
		cout << "两个立方体不相等" << endl;
	}

	if (MycompareCube(m1,m2))
	{
		cout << "全局函数判断两个立方体相等" << endl;
	}
	else
	{
		cout << "全局函数判断两个立方体不相等" << endl;
	}

	system("pause");
	return 0;
}
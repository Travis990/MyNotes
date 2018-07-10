#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Circle
{ // 类的默认权限是私有
public: // 公有权限

	// 设置半径
	void setR(double r)
	{
		mR = r;
	}

	// 求周长
	double getL()
	{
		return 2 * 3.14 * mR;
	}

	double mR; // 半径
	// double a = 10; // 建议不要在类内直接赋值
	string name;
};

int main()
{
	//用自定义的数据类型定义变量
	//用类实例化对象
	Circle c;
	c.setR(100);
	cout << c.getL() << endl;

	system("pause");
	return 0;
}
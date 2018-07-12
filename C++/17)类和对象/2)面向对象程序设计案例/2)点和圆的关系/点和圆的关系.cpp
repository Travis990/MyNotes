#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"Circle.h"

// 全局函数判断点和圆的关系
void isCircleToPoint(Circle &c, Point &p)
{
	// 获取半径的平方
	double Tr = pow(c.getR(), 2);
	// 获取点到圆心距离的平方(x2-x1)^2+(y2-y1)^2
	double distance = pow(p.getX() - c.getHear().getX(), 2) + pow(p.getY() - c.getHear().getY(), 2);

	if (distance > Tr)
	{
		cout << "全局判断点在圆外" << endl;
	}
	else if (distance == Tr)
	{
		cout << "全局判断点在圆上" << endl;
	}
	else
	{
		cout << "全局判断点在圆内" << endl;
	}
}

int main()
{
	// 实例化圆对象
	Point point;
	point.setX(30);
	point.setY(10);

	// 实例化圆对象
	Circle circle;
	circle.setR(10);
	circle.setHear(10, 10);

	circle.isCircleByPoint(point);

	isCircleToPoint(circle, point);

	system("pause");
	return 0;
}
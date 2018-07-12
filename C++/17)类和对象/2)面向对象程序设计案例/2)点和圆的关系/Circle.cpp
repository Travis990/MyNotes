#include "Circle.h"

void Circle::setR(int r)
{
	mR = r;
}

int Circle::getR()
{
	return mR;
}

void Circle::setHear(Point &hear)
{
	mHear.setX(hear.getX());
	mHear.setY(hear.getY());
}
void Circle::setHear(int x, int y)
{
	mHear.setX(x);
	mHear.setY(y);
}

Point Circle::getHear()
{
	return mHear;
}

// 判断点和圆的关系
void Circle::isCircleByPoint(Point &point)
{
	// 获取半径的平方
	double Tr = pow(mR, 2);
	// 获取点到圆心距离的平方(x2-x1)^2+(y2-y1)^2
	double distance = pow(point.getX() - mHear.getX(), 2) + pow(point.getY() - mHear.getY(), 2);

	if (distance > Tr)
	{
		cout << "点在圆外" << endl;
	}
	else if (distance == Tr)
	{
		cout << "点在圆上" << endl;
	}
	else
	{
		cout << "点在圆内" << endl;
	}
}

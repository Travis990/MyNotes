#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include"Point.h"
using namespace std;

class Circle
{
public:
	void setR(int r);
	int getR();
	void setHear(Point &hear);
	void setHear(int x, int y);
	Point getHear();
	void isCircleByPoint(Point &point);
public:
	int mR; // °ë¾¶
	Point mHear; // Ô²ÐÄ
};
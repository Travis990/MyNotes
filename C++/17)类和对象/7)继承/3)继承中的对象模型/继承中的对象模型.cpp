#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Father
{
public: // 公有
	int a;
private: // 私有
	int b;
protected: // 保护
	int c;
};

class Son :public Father
{
public:
	int d;
};

int main()
{


	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

class Girl
{
public:
	Girl(){}
	Girl(const char *str, int age)
	{
		cout << "有参构造函数" << endl;
		name = (char*)malloc(strlen(str) + 1);
		strcpy(name, str);
		this->age = age;
	}

	void printGirl()
	{
		cout << "name:" << name << " age:" << age << endl;
	}

	// 析构函数
	~Girl()
	{
		cout << "析构函数" << endl;
		if (NULL != name)
		{
			free(name);
			name = NULL;
		}
	}
public:
	char *name;
	int age;
};

void test()
{
	//Girl girl;  // 当用户自定义了有参构造函数, 编译器将不提供给默认的构造函数, 如需要无参构造函数需用户手动定义
	Girl girl("小姐姐", 18);
	girl.printGirl();
}

int main()
{
	test();

	system("pause");
	return 0;
}
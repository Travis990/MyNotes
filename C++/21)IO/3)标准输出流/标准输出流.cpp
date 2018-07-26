#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
using namespace std;

void test()
{
	cout.put('c');

	cout.put('h').put('e').put('l').put('l').put('o').put('\n');
	cout << "hello" << endl;
}

void test02()
{
	char buf[] = "hello";
	cout.write(buf, strlen(buf));
}

// 格式化输出数据，通过成员函数
void test03()
{
	int num = 99;
	cout.width(20); // 设置宽度
	cout.fill('*'); // 填充字符
	cout.setf(ios::left); // 让数据放到左边
	cout.unsetf(ios::dec); // 卸载十进制
	cout.setf(ios::hex); // 安装十六进制
	cout.setf(ios::showbase); // 显示基数
	cout.unsetf(ios::hex);
	cout.setf(ios::oct);
	cout << num << endl;
}

// 用控制符格式化输出数据,引入头文件iomanip
void test04()
{
	int num = 99;
	cout << setw(20); // 设置宽度
	cout << setfill('~'); // 填充字符
	cout << setiosflags(ios::left); // 让数据放到左边
	cout << setiosflags(ios::showbase); // 显示基数
	cout << hex;
	cout << oct;
	cout << dec;
	cout << num << endl;
}

void test05()
{
	double d = 30.33;
	cout << setiosflags(ios::fixed);
	cout << setprecision(10) << d << endl; // 10表示打印小数点后几位
}

int main()
{
	test05();

	system("pause");
	return 0;
}
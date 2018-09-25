#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>//文件读写的头文件
using namespace std;

//输出到缓冲区（写文件）
void test01()
{
	ofstream ofs;//文件流对象
	ofs.open("test.txt", ios::out | ios::trunc);
	//判断是否打开成功
	if (!ofs.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	//写文件
	ofs << "姓名:悟空" << endl;
	ofs << "身高:180cm" << endl;
	ofs << "年龄:18" << endl;

	//关闭文件
	ofs.close();
}

//输入到缓冲区（读文件)
void test02()
{
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "打开文件失败" << endl;
	}

	//读文件
	char buf[1024] = { 0 };
	//每次读取一行数据
	/*while (ifs>>buf)
	{
		cout << buf << endl;
	}*/

	/*while (!ifs.eof())
	{
		ifs.getline(buf, sizeof(buf));
		cout << buf << endl;

	}*/

	char c;
	while ((c=ifs.get())!=EOF)
	{
		cout << c;
	}


	ifs.close();
}

int main()
{
	test02();
	system("pause");
	return EXIT_SUCCESS;
}


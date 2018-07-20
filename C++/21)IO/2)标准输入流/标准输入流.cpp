#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
缓冲区
cin.get() //一次只能读取一个字符
cin.get(一个参数) //读一个字符
cin.get(两个参数) //可以读字符串
cin.getline()
cin.ignore()
cin.peek()
cin.putback()

*/

// cin.get() //一次只能读取一个字符
void test01()
{
	/*
	char a = cin.get(); // 一次读取一个字符
	cout << a << endl; // a

	a = cin.get();
	cout << a << endl; // s

	a = cin.get();
	cout << a << endl; // 获取回车

	a = cin.get();
	cout << a << endl;

	char ch = '0';
	cin.get(ch);
	cout << ch << endl;
	*/
	char a, b, c;
	cin.get(a).get(b).get(c);
	cout << a << b << c << endl;
}

// cin.get（2个参数）
void test02()
{
	char buf[1024] = { 0 };

	//cin.get(buf,1024);//获取1024个字符，但是换行符留在缓冲区
	//char c = cin.get();
	//if (c =='\n')
	//{
	//	cout << "换行符还在缓冲区" << endl;
	//}
	//cout << buf << endl;
	//cout << c << endl;

	//cin.getline()//换行符丢掉
	cin.getline(buf, 1024);
	char c = cin.get(); // 这里会阻塞
	if (c == '\n')
	{
		cout << "换行符还在缓冲区" << endl;
	}
	cout << buf << endl;
	cout << c << endl;
}

// cin.ignore() 忽略 没有参数就忽略一个字符，参数是N，表示忽略N个字符
void test03()
{
	cin.ignore(2);
	char c = cin.get();
	cout << c << endl;
}

// cin.peek() 偷窥，只看不拿走
void test04()
{
	char c = cin.peek();
	cout << c << endl;

	c = cin.get();
	cout << c << endl;
}

// cin.putback() 放回到缓冲区
void test05()
{
	char c = cin.get();

	cin.putback(c); // 放回
	char buf[1024] = { 0 };
	cin.getline(buf, 1024);
	cout << buf << endl;
}

// 判断用户输入的是字符串还是数字
void test06()
{
	cout << "请输入字符串或数字:" << endl;

	char c = cin.peek();
	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "你输入的数字是：" << num << endl;
	}
	else if (c >= 'A' && c <= 'Z')
	{
		char buf[1024] = { 0 };
		cin >> buf;

		cout << "你输入的首字母是大写的字符串:" << buf << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;

		cout << "你输入的字符串:" << buf << endl;
	}
}

// 输入一个0到10之间的数，直到输入正确为止
void test07()
{
	int num;
	while (1)
	{
		cin >> num; // 缓冲区如果还有数据，这里不会阻塞
		if (num >= 0 && num <= 10)
		{
			cout << "输入正确" << endl;
			break;
		}

		cout << "请重新输入:" << endl;

		cin.clear();//重置标志位，标志位变为0
		cin.sync();//清空缓冲区 qt setbuf(stdin,NULL)

		////打印标志位
		//cout << cin.fail() << endl;
		//vs2015 或2017
		/*char buf[1024] = { 0 };
		cin.getline(buf, 1024);*/
	}
}

int main()
{
	test07();

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

void test()
{
	// 数据结构：连续的，超过16个字节就从堆区申请空间
	// 迭代器
	string::iterator it;
	it++;
	it--;
	it + 2;
	// 双向，随机
}

/*
string();//创建一个空的字符串 例如: string str;
string(conststring& str);//使用一个string对象初始化另一个string对象
string(constchar* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化

*/

void test01()
{
	// 是类模版，但是不要<>，是因为取了别名
	string s1;
	string s2(10, 'a');

	string s3(s2);
	string s4("hello");
}

/*
string&operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string&operator=(const string&s);//把字符串s赋给当前的字符串
string&operator=(char c);//字符赋值给当前的字符串
string& assign(constchar *s);//把字符串s赋给当前的字符串
string& assign(constchar *s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(conststring&s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(conststring&s, int start, int n);//将s从start开始n个字符赋值给字符串,如s=hello,那么n=3,start=1，那么是hel中从e开始赋值3-1个字符

*/

void test02()
{
	string s1;
	s1 = "hello";
	cout << s1 << endl;

	string s2;
	s2.assign("world");
	cout << s2 << endl;
}

/*
char&operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符

*/

void test03()
{
	string s = "hello world";

	for (int i = 0; i < s.size(); i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < s.size(); i++)
	{
		cout << s[100] << endl;
		//cout<<s.at()<<" ";
	}
	cout << endl;

	//[]和at的区别：
	//[]访问越界不抛异常，直接挂
	//at越界抛异常

	try
	{
		cout << s.at(100) << endl;
	}
	catch (out_of_range &ex)
	{
		cout << ex.what() << endl;
		cout << "捕获异常" << endl;
	}
}

/*
string&operator+=(conststring& str);//重载+=操作符
string&operator+=(constchar* str);//重载+=操作符
string&operator+=(constchar c);//重载+=操作符
string& append(constchar *s);//把字符串s连接到当前字符串结尾
string& append(constchar *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
string& append(conststring&s);//同operator+=()
string& append(conststring&s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c);//在当前字符串结尾添加n个字符c

*/

void test04()
{
	string s1 = "aaa";
	s1 += "bbb";
	s1 += 'c';
	cout << s1 << endl;

	s1.append("dddddd", 3);
	cout << s1 << endl; // aaabbbcddd
}

/*
int find(conststring& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(constchar* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(constchar* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(constchar c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(conststring& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(constchar* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(constchar* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(constchar c, int pos = 0) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, conststring& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, constchar* s); //替换从pos开始的n个字符为字符串s

*/

void test05()
{
	string s = "abcdefgaafsd";

	cout << s.find('d') << endl; // 3
	cout << s.rfind('d') << endl; // 11,查找是从右到左，但是数字是从左到右

	cout << s.find("kkk") << endl; // 不是返回-1

	s.replace(2, 4, "AAAAB"); // 从2的位置（下标从0开始），替换4个字符，
	// 如果没有4个字符来替换，那么剩余的字符会被消除,如果大于4个字符，也会插入到字符串中
	cout << s << endl;
}

/*

compare函数在>时返回 1，<时返回 -1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。

int compare(conststring&s) const;//与字符串s比较
int compare(constchar *s) const;//与字符串s比较

*/

void test06()
{
	string s1 = "hello";
	string s2 = "hello";

	const char* s = "world";

	if (s1.compare(s2) == 0)
	{
		cout << "s1==s2" << endl;
	}

	if (s1.compare(s) == 0)
	{
		cout << "s1==s" << endl;
	}
}

/*
string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
*/

void test07()
{
	string email = "hello world@itcast.cn";
	int pos = email.find('@');

	string username = email.substr(0, pos);
	cout << username << endl;

	string prex = email.substr(pos + 1);
	cout << prex << endl;
}

/*
string& insert(int pos, constchar* s); //插入字符串
string& insert(int pos, conststring& str); //插入字符串
string& insert(int pos, int n, char c);//在指定位置插入n个字符c
string& erase(int pos, int n = npos);//删除从Pos开始的n个字符

*/
void test08()
{
	string s = "aaaaa";
	s.insert(3, "AAAA"); // 从3的位置插入字符串"AAAA"
	cout << s << endl;

	s.insert(3, 5, 'M'); // 从3的位置插入5个M字符
	cout << s << endl;

	s.erase(2, 3);
	cout << s << endl;
}

/*
//string 转 char*
string str = "itcast";
constchar* cstr = str.c_str();
//char* 转 string
char* s = "itcast";
string sstr(s);

*/
void test09()
{
	const char *str = "hello";

	string s(str);
	cout << s << endl;

	const char *s2 = s.c_str();
	cout << s2 << endl;
}

// []和at返回的是引用，重新分配空间，可能会出错
void test10()
{
	string s = "abcde";
	char &a = s[2];
	char &b = s[3];

	a = '1';
	b = '2';

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	cout << s << endl;
	cout << "字符串原来的地址:" << (int*)s.c_str() << endl;

	s = "dfasflsafadsfafdafdasfadsfsafsadfsdafasfdsfdaf";

	cout << "字符串的地址：" << (int*)s.c_str() << endl;

	//字符串的空间会被重新分配，原来的引用就不能用了
	//a = '3';//会档 error
}

void test11()
{
	string s = "hello world";
	for (string::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	// 反向遍历
	for (string::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}


int main()
{
	test11();

	system("pause");
	return 0;
}
#include "MyString.h"



MyString::MyString()
{
	this->p = new char[1];
	this->p[0] = '\0';
	this->mSize = 0;
}


MyString::~MyString()
{
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
}

MyString::MyString(int n, char c) // 让用户来初始化数据，n个c字符组成字符串
{
	this->p = new char[n + 1];
	for (int i = 0; i < n; i++)
	{
		this->p[i] = c;
	}
	this->p[n] = '\0';
	this->mSize = n;
}

// 拷贝构造
MyString::MyString(const MyString& str)
{
	this->p = new char[strlen(str.p) + 1];
	strcpy(this->p, str.p);
	this->mSize = str.mSize;
}

// 赋值函数
MyString& MyString::operator=(const MyString& str)
{
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
	this->p = new char[strlen(str.p) + 1];
	strcpy(this->p, str.p);
	this->mSize = str.mSize;
	return *this;
}

// MyString str3=str1+str2;
MyString MyString::operator+(const MyString& str)
{
	// 1.定义一个临时变量
	MyString tmp; // 调用无参构造函数
	// 2.释放这个变量中的堆区空间
	if (NULL != tmp.p)
	{
		delete[] tmp.p;
		tmp.p = NULL;
	}

	// 3.申请空间，空间的大小是str1+str2的堆区空间大小
	int newstrlen = this->mSize + str.mSize;
	tmp.p = new char[newstrlen + 1];
	tmp.mSize = newstrlen;

	// 拷贝数据到空间中
	memset(tmp.p, 0, newstrlen + 1);
	strcat(tmp.p, this->p);
	strcat(tmp.p, str.p);

	return tmp;
}

MyString MyString::operator+(const char *s)
{
	/*
	//1.定义一个临时变量
	MyString tmp;//调用无参构造函数
	//2.释放这个变量中的堆区空间
	if (tmp.p != NULL)
	{
	delete[] tmp.p;
	tmp.p = NULL;
	}

	//3.申请空间，空间的大小是str1+str2的堆区空间大小
	int newstrlen = this->mSize + strlen(s) + 1;
	tmp.p = new char[newstrlen];
	memset(tmp.p, 0, newstrlen);

	tmp.mSize = this->mSize + strlen(s);

	//拷贝数据到空间中
	strcat(tmp.p, this->p);
	strcat(tmp.p, s);

	return tmp;
	*/

	/*MyString str4=str1+"hello";
	MyString str4 = str3 + "hello";
	cout << str4 << endl;*/

	int newstrlen = this->mSize + strlen(s);
	char *tmp = new char[newstrlen + 1];
	memset(tmp, 0, newstrlen + 1);
	strcat(tmp, this->p);
	strcat(tmp, s);

	// 释放原来的空间
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
	this->p = tmp; // 把新地址给this;
	this->mSize = newstrlen;
	return *this;
}

// str4 += str3;
MyString& MyString::operator+=(const MyString& str)
{
	// 1.获取两个字符串的长度
	int newstrlen = this->mSize + str.mSize;
	// 2.申请空间
	char *newp = new char[newstrlen + 1];
	// 3.把数据追加到空间
	memset(newp, 0, newstrlen + 1);
	strcat(newp, this->p);
	strcat(newp, str.p);
	// 4.释放str4的堆区空间
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
	// 5.把新申请的堆区空间地址给对象中的指针
	this->p = newp;
	this->mSize = newstrlen;
	return *this;
}

MyString& MyString::operator+=(const char *s)
{
	// 1.获取两个字符串的长度
	int newstrlen = this->mSize + strlen(s);
	// 2.申请空间
	char *newp = new char[newstrlen + 1];
	// 3.把数据追加到空间
	memset(newp, 0, newstrlen + 1);
	strcat(newp, this->p);
	strcat(newp, s);
	// 4.释放str4的堆区空间
	if (NULL != this->p)
	{
		delete[] this->p;
		this->p = NULL;
	}
	// 5.把新申请的堆区空间地址给对象中的指针
	this->p = newp;
	this->mSize = newstrlen;
	return *this;
}

int MyString::Size()
{
	return this->mSize;
}

char& MyString::operator[](int index)
{
	return this->p[index];
}

// cout<<str;
ostream& operator<<(ostream& out, MyString& str)
{
	out << str.p;
	return out;
}

// cin >> str4;
istream& operator >> (istream& in, MyString& str)
{
	// 1.定义空间
	char tmp[1024] = { 0 };
	// 2.获取用户输入的信息
	in >> tmp;
	// 3.释放原来的空间  
	if (NULL != str.p)
	{
		delete[] str.p;
		str.p = NULL;
	}
	// 4.申请新的堆区空间
	str.p = new char[strlen(tmp) + 1];
	memset(str.p, 0, strlen(tmp) + 1);
	// 5.拷贝用户输入的信息到堆区空间
	strcpy(str.p, tmp);
	str.mSize = strlen(tmp);
	return in;
}

#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<string>
using namespace std;

class MyString
{
	friend ostream& operator<<(ostream& out, MyString& str);
	friend istream& operator >> (istream& in, MyString& str);
public:
	MyString();
	MyString(int n, char c); // 让用户来初始化数据，n个c字符组成字符串
	// 拷贝构造
	MyString(const MyString& str);
	// 赋值函数
	MyString& operator=(const MyString& str);
	~MyString();

	MyString operator+(const MyString& str);
	MyString operator+(const char *s);

	MyString& operator+=(const MyString& str);
	MyString& operator+=(const char *s);

	int Size();

	char& operator[](int index);

	/*
	MyString str1;
	MyString str2;
	MyString str3=str1+str2;
	MyString str4=str1+"hello";

	str4+=str3;
	str4+="hello";
	//如果要打印私有成员变量，那么左右移函数要写成类的友元函数
	cout<<str4<<endl;
	cin>>str4;

	*/

private:
	char *p;
	int mSize;
};


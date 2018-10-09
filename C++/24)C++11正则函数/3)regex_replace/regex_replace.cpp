#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <regex>
#include <string>
#include <iterator>
using namespace std;

// 1) 使用字符串类型替换字符
void test01()
{
	string s("there is a subsequence in the string\n");
	regex e("\\b(sub)([^ ]*)");  // matches words beginning by "sub" -- 匹配文字从"sub"开始

	// using string/c-string (3) version:
	cout << regex_replace(s, e, "sub-$2");
}

// 2) 使用范围替换字符
void test02()
{
	string s("there is a subsequence in the string\n");
	regex e("\\b(sub)([^ ]*)");  // matches words beginning by "sub" -- 匹配文字从"sub"开始

	// using range/c-string (6) version:
	string result;
	regex_replace(back_inserter(result), s.begin(), s.end(), e, "$2");
	cout << result << endl;

	// 使用 标志 flags
	// regex_constants::format_no_copy 仅获得替换结果,不进行拷贝原文副本
	cout << regex_replace(s, e, "$1 and $2", regex_constants::format_no_copy) << endl;
	cout << regex_replace(s, e, "$1 and $2") << endl;
}

int main()
{
	test02();

	system("pause");
	return 0;
}
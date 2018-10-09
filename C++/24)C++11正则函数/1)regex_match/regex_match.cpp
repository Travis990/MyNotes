#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <regex>
using namespace std;

// 1) 字符串文字匹配
void test01()
{
	if (regex_match("subject", regex("(sub)(.*)")))
	{
		cout << "匹配到字符串!\n";
	}
}

// 2) 字符串对象匹配
void test02()
{
	string s("subject");
	regex e("(sub)(.*)");
	if (regex_match(s, e))
	{
		cout << "匹配到字符串!\n";
	}
}

// 3) 范围匹配
void test03()
{
	string s("subject");
	regex e("(sub)(.*)");
	if (regex_match(s.begin(), s.end(), e))
	{
		cout << "匹配到字符串!\n";
	}
}

// 4) char*类型查找匹配
void test04()
{
	//const char cstr[] = "subject"; 等同↓
	const char *cstr = "subject";
	cmatch cm;   // same as std::match_results<const char*> cm;
	regex e("(sub)(.*)");
	regex_match(cstr, cm, e);
	cout << "匹配到结果有 " << cm.size() << " 个\n";
}

// 5) string类型查找匹配
void test05()
{
	string s("subject");
	smatch sm; // same as std::match_results<string::const_iterator> sm;
	regex e("(sub)(.*)");
	regex_match(s, sm, e);
	cout << "匹配到结果有 " << sm.size() << " 个\n";

	regex_match(s.cbegin(), s.cend(), sm, e);
	cout << "匹配到结果有 " << sm.size() << " 个\n";
}

// 6) 标记 & 打印匹配结果
void test06()
{
	const char *cstr = "subject";
	cmatch cm;   // same as std::match_results<const char*> cm;
	regex e("(sub)(.*)");

	// 使用 标志 regex_constants::match_default
	regex_match(cstr, cm, e, regex_constants::match_default);

	cout << "匹配到的结果: ";
	for (unsigned i = 0; i < cm.size(); ++i)
	{
		cout << "[" << cm[i] << "]";
	}
	cout << endl;
}

int main()
{
	test04();
	test06();

	system("pause");
	return 0;
}
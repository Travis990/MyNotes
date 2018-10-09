#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <regex>
using namespace std;

void test01()
{
	string s("this subject has a submarine as a subsequence");
	smatch sm;
	regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub" -- 匹配文字从"sub"开始

	cout << "匹配目标: " << s << endl;
	cout << "匹配规则: /\\b(sub)([^ ]*)/" << endl;
	cout << "找到以下匹配和子匹配:" << endl;

	while (regex_search(s, sm, e))
	{
		//for (auto x : sm) cout << x << " "; // 等同于↓
		for(smatch::iterator it = sm.begin(); it != sm.end(); ++it) cout << *it << " ";

		cout << endl;
		s = sm.suffix().str();
	}
}

int main()
{
	test01();

	system("pause");
	return 0;
}
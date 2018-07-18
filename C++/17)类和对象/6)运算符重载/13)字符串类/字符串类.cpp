#include "MyString.h"

void test()
{
	MyString str1(10, 'a');
	cout << str1 << endl;

	MyString str2(3, 'b');
	cout << str2 << endl;

	MyString str3 = str1 + str2;
	cout << str3 << endl;

	MyString str4 = str3 + "hello";
	cout << str4 << endl;
	cout << "-----------------------" << endl;
	str4 += str3;
	cout << str4 << endl;

	str4 += "Dejan";
	cout << str4 << endl;

	cin >> str4;
	cout << str4 << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}
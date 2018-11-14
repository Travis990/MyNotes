#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <XUdp.h>
#include <regex>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	unsigned short port = 514;
	XUdp syslog;
	if (!syslog.Bind(port))
	{
		return -1;
	}

	char buf[2000] = { 0 };
	for (;;)
	{
		int len = syslog.Recv(buf, sizeof(buf));
		if (len <= 0)
		{
			continue;
		}
		buf[len] = '\0';

		// Failed password for root from 192.168.163.1 port 20224 ssh2
		string src = buf;
		string reg = "Failed password for ([a-zA-Z0-9]+) from ([0-9.]+)";
		regex r(reg);
		smatch mas;
		regex_search(src, mas, r);
		if (mas.size() > 0)
		{
			cout << "Warning: User " << mas[1] << "@" << mas[2] << " login failed!"<<endl;
		}
		//cout << buf << endl;
	}

	system("pause");
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <XUdp.h>
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
		cout << buf << endl;
	}

	system("pause");
	return 0;
}
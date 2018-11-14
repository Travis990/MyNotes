#include "XHttpClient.h"
#include <thread>
using namespace std;

bool XHttpClient::Start(XTcp client)
{
	this->client = client;
	thread sth(&XHttpClient::Main, this);
	sth.detach();
	return true;
}

void XHttpClient::Main()
{
	char buf[10240] = {0};
	for(;;)
	{
		int len = client.Recv(buf, sizeof(buf)-1);
		if (len <= 0)
		{
			break;
		}
		buf[len] = '\0';
		if (!res.SetRequest(buf))
		{
			break;
		}
		string head = res.GetHead();
		if (client.Send(head.c_str(), head.size()) <= 0)
		{
			break;
		}
		int size = sizeof(buf);
		bool error = false;
		for (;;)
		{
			int len = res.Read(buf, size);
			if (len <= 0)
			{
				error = true;
				break;
			}
			if (len == 0) break;
			if (client.Send(buf, len) <= 0)
			{
				error = true;
				break;
			}
		}
	}
	client.Close();
	delete this;
}

XHttpClient::XHttpClient()
{
}


XHttpClient::~XHttpClient()
{
}

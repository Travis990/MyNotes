#include "XHttpServer.h"
#include "XHttpClient.h"
#include <thread>
using namespace std;

bool XHttpServer::Start(unsigned short port)
{
	server.CreateSocket();
	if (!server.Bind(port)) return false;
	thread sth(&XHttpServer::Main, this);
	sth.detach();
	return true;
}

void XHttpServer::Main()
{
	while (!isexit)
	{
		XTcp client = server.Accept();
		if (client.sock <= 0) continue;
		XHttpClient *th = new XHttpClient();
		th->Start(client);
	}
}

void XHttpServer::Stop()
{
	isexit = true;
}

XHttpServer::XHttpServer()
{
}


XHttpServer::~XHttpServer()
{
}

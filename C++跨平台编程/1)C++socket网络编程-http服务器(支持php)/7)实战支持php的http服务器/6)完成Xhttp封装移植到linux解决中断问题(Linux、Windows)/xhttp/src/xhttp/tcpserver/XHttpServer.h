#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <XTcp.h>

class XHttpServer
{
public:
	bool Start(unsigned short port);
	void Main();
	void Stop();

	XHttpServer();
	~XHttpServer();

public:
	XTcp server;
	bool isexit = false;
};


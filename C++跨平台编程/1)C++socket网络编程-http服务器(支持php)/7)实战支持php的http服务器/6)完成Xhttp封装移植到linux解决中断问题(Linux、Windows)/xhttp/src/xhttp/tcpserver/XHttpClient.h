#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <XTcp.h>
#include "XHttpResponse.h"

class XHttpClient
{
public:
	bool Start(XTcp client);
	void Main();

	XHttpClient();
	~XHttpClient();

public:
	XTcp client;
	XHttpResponse res;
};


#pragma once

class XTcp
{
public:
	int CreateSocket();
	bool Bind(unsigned short port);
	XTcp Accept();
	void Close();
	int Recv(char* buf, int bufsize);
	int Send(const char* buf, int bufsize);

	XTcp();
	virtual ~XTcp();

public:
	int sock = 0;
	unsigned short port = 0;
	std::string ip;
};


#ifndef XTCP_H
#define XTCP_H

#ifdef WIN32
	#ifdef XSOCKET_EXPORTS
	#define XSOCKET_API __declspec(dllexport)
	#else
	#define XSOCKET_API __declspec(dllimport)
	#endif
#else
	#define XSOCKET_API
#endif

class XSOCKET_API XTcp
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
	char ip[16];
};

#endif
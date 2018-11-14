#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "XHttpServer.h"
#ifdef WIN32
#else
#include <signal.h>
#endif // Linux



int main(int argc, char** argv)
{
#ifdef WIN32
#else
	signal(SIGPIPE, SIG_IGN);
#endif // Linux
	
	unsigned short port = 8080;
	if (argc > 1) port = atoi(argv[1]);

	XHttpServer server;
	server.Start(port);

	getchar();
	return 0;
}
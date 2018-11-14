#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#ifdef WIN32
#include <Windows.h>
#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
using namespace std;

int main(int argc, char** argv)
{
	unsigned short port = 8080;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}

#ifdef WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2,2), &ws);
#endif

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock <= 0)
	{
		cout << "create socket failed!" << endl;
		return -1;
	}
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);
	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		cout << "bind port " << port << "failed!" << endl;
		return -2;
	}
	cout << "bind port " << port << "success!" << endl;
	listen(sock, 10);
	sockaddr_in client;
	socklen_t len = sizeof(client);
	char buf[10240] = {0};
	int re = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr*)&client, &len);
	if (re <= 0)
	{
		cout << "recvFrom failed!" << endl;
		return -3;
	}
	cout <<"recv"<<inet_ntoa(client.sin_addr)<<":"<< ntohs(client.sin_port) << endl;

	buf[re] = '\0';
	cout << buf << endl;
	sendto(sock, "67890", 6, 0, (sockaddr*)&client, sizeof(client));

	getchar();
	return 0;
}
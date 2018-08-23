#include <stdio.h>
#include <arpa/inet.h>

/*
#include <arpa/inet.h>
int inet_pton(int af, const char *src, void *dst);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
支持IPv4和IPv6
可重入函数
其中inet_pton和inet_ntop不仅可以转换IPv4的in_addr，还可以转换IPv6的in6_addr。
因此函数接口是void *addrptr。

 */

int main()
{
	unsigned char ip[16] = "192.168.1.2";
	unsigned int num = 0;
	inet_pton(AF_INET, ip, &num);
	unsigned char *p = (unsigned char *)&num;

	printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));
	char buf[INET_ADDRSTRLEN] = {0};
	// char *buf; err
	inet_ntop(AF_INET, &num, buf, 16); // "255.255.255.254\0" => 16个字节
	
	printf("buf = %s\n", buf);
	printf("%d\n", num);

	return 0;
}

#include <stdio.h>
#include <arpa/inet.h>

/* 网络字节序和主机字节序的转换

#include <arpa/inet.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

*/

int main()
{
	int num = 0x01020304;
	int sum = 0;
	sum = htonl(num); // 将num小端的数据转大端的存在sum中
	printf("sum = %x\n", sum);
	// 将sun大端的数据转小端
	int a = ntohl(sum);
	printf("a = %x\n", a);

	return 0;
}

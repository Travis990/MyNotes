#include <stdio.h>
#include <string.h>
#include "base64.h"

int main()
{
	
	//bindata编码成base64
	//bindata：  源字符串
	//binlength: 源字符串长度
	//base64：目的字符串，base64字符串
	//返回值：base64字符串
	//char * base64_encode( const unsigned char * bindata, int binlength, char * base64 );
	char src[] = "我爱C语言";
	int src_len = strlen(src);
	
	char base64[1024] = {0};
	base64_encode(src, src_len, base64); //base64编码
	printf("base64 = %s\n", base64);
	
	memset(src, 0, sizeof(src) );
	src_len = 0;
	
	//解码base64
	//base64：源字符串
	//bindata: 目的字符串
	//返回值：目的字符串长度
	//int base64_decode( const char * base64, unsigned char * bindata );
	src_len = base64_decode(base64, src);
	printf("src = %s, strlen(src) = %lu, src_len = %d\n", src, strlen(src), src_len);
	
	
	return 0;
}
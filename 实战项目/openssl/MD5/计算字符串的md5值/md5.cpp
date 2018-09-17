#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<openssl/md5.h>
#include<string>
using namespace std;

// 方式1:
char* md5(const char *src, char *dst)
{
	MD5_CTX ctx;
	// 初始化
	MD5_Init(&ctx);
	// 添加数据
	MD5_Update(&ctx, src, MD5_DIGEST_LENGTH * 2 + 1);
	// 计算结果
	unsigned char md[MD5_DIGEST_LENGTH] = { 0 };
	MD5_Final(md, &ctx);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		sprintf(&dst[i * 2], "%02x", md[i]);
	}
	return dst;
}

// 方式2:
char* md5_2(const char *src, char *dst)
{
	unsigned char md[MD5_DIGEST_LENGTH] = { 0 };
	MD5((unsigned char*)src, MD5_DIGEST_LENGTH * 2 + 1, md);
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		sprintf(&dst[i * 2], "%02x", md[i]);
	}
	return dst;
}


int main()
{
	char buf[33] = { 0 };
	cout <<"方式1: "<<md5("hello", buf) << endl;
	cout <<"方式2: "<< md5_2("hello", buf) << endl;

	system("pause");
	return 0;
}
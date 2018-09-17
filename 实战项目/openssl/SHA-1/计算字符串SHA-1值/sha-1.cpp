#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<openssl/sha.h>
using namespace std;

// 方式1:
char* sha1(const char *src, char *dst)
{
	SHA_CTX c;
	SHA1_Init(&c);
	SHA1_Update(&c, src, SHA_DIGEST_LENGTH);
	unsigned char md[SHA_DIGEST_LENGTH] = { 0 };
	SHA1_Final(md, &c);
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(&dst[i * 2], "%02x", md[i]);
	}
	return dst;
}

// 方式2:
char* sha1_2(const char *src, char *dst)
{
	unsigned char md[SHA_DIGEST_LENGTH] = { 0 };
	SHA1((unsigned char*)src, SHA_DIGEST_LENGTH, md);
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(&dst[i * 2], "%02x", md[i]);
	}
	return dst;
}

int main()
{
	char buf[41] = { 0 };
	cout << "方式1: " << sha1("hello world!", buf) << endl;
	cout << "方式2: " << sha1_2("hello world!", buf) << endl;

	system("pause");
	return 0;
}
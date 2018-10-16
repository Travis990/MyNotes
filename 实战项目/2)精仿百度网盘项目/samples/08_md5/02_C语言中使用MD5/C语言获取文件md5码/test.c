#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "md5.h"

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

int Compute_file_md5(const char *file_path, char *value);

int Compute_file_md5(const char *file_path, char *md5_str)
{
	int i;
	FILE *fp;
	int ret;
	unsigned char data[READ_DATA_SIZE];
	unsigned char md5_value[MD5_SIZE];
	MD5_CTX md5;

	fp = fopen(file_path, "rb");
	if (NULL == fp)
	{
		perror("fopen");
		return -1;
	}

	// init md5
	MD5Init(&md5);

	while (1)
	{
		ret = fread(data,1,  READ_DATA_SIZE, fp);
		if (-1 ==  ret)
		{
			perror("read");
			return -1;
		}

		MD5Update(&md5, data, ret);

		if (0 == ret || ret < READ_DATA_SIZE)
		{
			break;
		}
	}

	fclose(fp);

	MD5Final(&md5, md5_value);

	char tmp[100] = { 0 };
	memset(md5_str, 0, MD5_STR_LEN + 1);

	for (i = 0; i < MD5_SIZE; i++)
	{
		sprintf(tmp, "%02x", md5_value[i]);
		strcat(md5_str, tmp);
	}
	//md5_str[MD5_STR_LEN] = '\0'; // add end

	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	const char *file_path = "1.jpg";
	char md5_str[MD5_STR_LEN + 1] = { 0 };

	ret = Compute_file_md5(file_path, md5_str);
	if (0 == ret)
	{
		printf("[file - %s] md5 value:\n", file_path);
		printf("%s\n", md5_str);
	}

	return 0;
}


#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itcast_asn1_der.h"

typedef struct _dejan
{
	char name[32];
	int age;
	char *p;
	int p_len;
}dejan;

// 导出内容到文件
int write_file(unsigned char*, int);
// 序列化函数 - asn1_serialize()
int asn1_serialize(dejan*, unsigned char**,int*);
// 反序列化函数 - asn1_unserialize()
int asn1_unserialize(unsigned char*, int, dejan**);
// 自定义结构体内存释放函数
int DejanStructFree(dejan**);

int main()
{
	/*---------------------Serialize Start------------------------*/
	unsigned char *dst_data = NULL;  // asn1序列化后编码
	int dst_data_len = 0; // asn1序列化后编码的长度

	// 定义一个dejan类的结构体变量
	dejan dj = {
		.name = "何德健",
		.age = 18,
		.p = "hello world!",
		.p_len = 12 
	};

	// 结构体dejan dj  =>   asn1序列化
	asn1_serialize(&dj, &dst_data, &dst_data_len);
	printf("ASN1编码成功!\n");
	printf("dst_data: %s\ndst_data_len: %d\n", dst_data, dst_data_len);
	// 输出到文件查看
	write_file(dst_data, dst_data_len);
	/*---------------------Serialize End------------------------*/


	/*---------------------Unserialize Start------------------------*/
	dejan *buf = NULL;  //解码之后传出参数
	asn1_unserialize(dst_data, dst_data_len, &buf);
	printf("解码成功... \n");

	// 比较结果(校检数据)
	if ((dj.age == buf->age) && strcmp(dj.name, buf->name) == 0)
	{
		printf("数据完整 OK!\n");
	}
	else 
	{
		printf("数据不完整! Failed!!\n");
	}

	printf("name:%s\nage:%d\np:%s\np_len:%d\n", buf->name, buf->age, buf->p, buf->p_len);
	// 释放内存
	DejanStructFree(&buf);

	/*---------------------Unserialize End------------------------*/


	system("pause");
	return 0;
}

/* asn1序列化编码
int asn1_serialize([自定义结构体类型变量], [输出内容], [输出内容长度]);
*/
int asn1_serialize(dejan *dj, unsigned char **dst_data, int *dst_data_len)
{
	ITCAST_ANYBUF *tmp_anybuf = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmp_node = NULL;
	ITCAST_ANYBUF *out_data_node = NULL;


	if (NULL == dj || NULL == dst_data || NULL == dst_data_len)
	{
		printf("参数不能为空!");
	}

	// 开始编码

	// 1. char name[32] == char*  =>  ANYBUF类型
	DER_ITCAST_String_To_AnyBuf(&tmp_anybuf, dj->name, strlen(dj->name)); 
	DER_ItAsn1_WritePrintableString(tmp_anybuf, &headNode); 

	// 2. int age  =>  ASN1编码
	tmp_node = headNode;
	DER_ItAsn1_WriteInteger(dj->age, &(tmp_node->next));

	// 3. char *p  =>  ASN1编码
	tmp_node = tmp_node->next;
	EncodeChar(dj->p, strlen(dj->p), &(tmp_node->next));

	// 4. int p_len   =>   ASN1编码
	tmp_node = tmp_node->next;
	DER_ItAsn1_WriteInteger(dj->p_len, &(tmp_node->next));

	// 5. 完整的链表结构体  =>  ASN1编码
	DER_ItAsn1_WriteSequence(headNode, &out_data_node);

	// 6. 传出
	unsigned char *out_data = NULL;
	int out_data_len = 0;
	out_data = malloc(out_data_node->dataLen);
	if (NULL == out_data)
	{
		perror("lin-97: error >> out_data = malloc(out_data_node->dataLen);");
	}
	memset(out_data, 0, out_data_node->dataLen + 1);
	memcpy(out_data, out_data_node->pData, out_data_node->dataLen);
	out_data_len = out_data_node->dataLen;

	*dst_data = out_data;
	*dst_data_len = out_data_len;

	// 7. 释放内存
	if (NULL != tmp_anybuf) 
	{
		DER_ITCAST_FreeQueue(tmp_anybuf);
	}
	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}
	if (NULL != out_data_node) 
	{
		DER_ITCAST_FreeQueue(out_data_node);
	}

	return 0;
}

/* 反asn1序列化编码
int asn1_unserialize([源内容], [源内容长度], [预输出到的空间地址])
*/
int asn1_unserialize(unsigned char *src_data, int src_data_len, dejan **dst_data)
{
	ITCAST_ANYBUF *tmp_anybuf = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmp_node = NULL;
	ITCAST_ANYBUF *out_data_node = NULL;

	dejan *buf = NULL;

	if (NULL == src_data || NULL == src_data_len || NULL == dst_data)
	{
		perror("参数不能为空!");
	}

	// 1. 把结构体ASN1编码  =>  AnyBuf
	DER_ITCAST_String_To_AnyBuf(&tmp_anybuf, src_data, src_data_len);
	DER_ItAsn1_ReadSequence(tmp_anybuf, &headNode);

	// 给 buf分配空间
	buf = malloc(sizeof(dejan));
	if (NULL == buf)
	{
		perror("buf = malloc(sizeof(dejan));");
	}
	memset(buf, 0, sizeof(dejan));

	// 2. (ASN1)name   =>   (char*)name
	ITCAST_ANYBUF *tmp_name = NULL;
	DER_ItAsn1_ReadPrintableString(headNode, &tmp_name);

	// 拷贝数据
	memcpy(buf->name, tmp_name->pData, tmp_name->dataLen);

	// 3. (ASN1)age   =>    int age
	tmp_node = headNode->next;
	DER_ItAsn1_ReadInteger(tmp_node, &buf->age);

	// 4. (ASN1)p     =>     (char*)p
	ITCAST_ANYBUF *tmp_p;
	tmp_node = tmp_node->next;
	DER_ItAsn1_ReadPrintableString(tmp_node, &tmp_p);

	// 分配空间
	buf->p = malloc(tmp_p->dataLen + 1);
	if (NULL == buf->p)
	{
		perror("buf->p = malloc(tmp_p->dataLen + 1)");
	}
	memset(buf->p, 0, tmp_p->dataLen + 1);

	// 拷贝数据
	memcpy(buf->p, tmp_p->pData, tmp_p->dataLen);

	// 5. (ASN1)p_len   =>  (char*)p_len
	tmp_node = tmp_node->next;
	DER_ItAsn1_ReadInteger(tmp_node, &buf->p_len);

	// 6. 传出
	*dst_data = buf;

	// 7. 释放内存
	if (NULL != tmp_anybuf)
	{
		DER_ITCAST_FreeQueue(tmp_anybuf);
	}
	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}
	if (NULL != tmp_name)
	{
		DER_ITCAST_FreeQueue(tmp_name);
	}
	if (NULL != tmp_p)
	{
		DER_ITCAST_FreeQueue(tmp_p);
	}
	return 0;
}

/* 导出内容到文件
write_file([内容], [内容长度])
*/
int write_file(unsigned char *buf, int len)
{
	FILE *fp = NULL;
	fp = fopen("./teacher.ber", "wb");
	if (NULL == fp)
	{
		printf("fopen file error \n");
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	return 0;
}

/*自定义结构体内存释放函数
int DejanStructFree([自定义结构体指针的地址])
*/
int DejanStructFree(dejan **dj)
{
	dejan *buf = NULL;
	if (NULL == dj || NULL == *dj)
	{
		perror("error:int DejanStructFree(dejan **dj)");
	}
	buf = *dj;

	// 释放 (*dj)->p 指向的空间
	if (NULL != buf->p)
	{
		free(buf->p);
	}
	// 释放外层结构体
	free(buf);
	buf = NULL;
	*dj = NULL;

	return 0;
}
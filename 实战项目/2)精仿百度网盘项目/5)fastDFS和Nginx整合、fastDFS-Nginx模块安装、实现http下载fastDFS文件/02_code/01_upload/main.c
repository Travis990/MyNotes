/*
 * echo.c --
 *
 *	Produce a page containing all FastCGI inputs
 *
 *
 * Copyright (c) 1996 Open Market, Inc.
 *
 * See the file "LICENSE.TERMS" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */
#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

#include "fcgi_config.h"

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#include <fcntl.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
//就是环境变量的数组
extern char **environ;
#endif

#include "fcgi_stdio.h"
#include <assert.h>
#include <string.h>

int read_file(char *data , size_t len,
        char *out_file_name , char *out_content_type,char **out_ptrBegin, char **out_ptrEnd);

//输出环境变量的一个函数
static void PrintEnv(char *label, char **envp)
{
    printf("%s:<br>\n<pre>\n", label);
    for ( ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

// find 'substr' from a fixed-length buffer 
// ('full_data' will be treated as binary data buffer)
// return NULL if not found
char* memstr(char* full_data, int full_data_len, char* substr)
{
    if (full_data == NULL || full_data_len <= 0 || substr == NULL)
    {
        return NULL;
    }

    if (*substr == '\0')
    {
        return NULL;
    }

    int sublen = strlen(substr);
    char* cur = full_data;
    int last_possible = full_data_len - sublen + 1;
    for (int i = 0; i < last_possible; i++)
    {
        if (*cur == *substr)
        {
            if (memcmp(cur, substr, sublen) == 0)
            {
                // found
                return cur;
            }
        }
        cur++;
    }

    return NULL;
}


int main ()
{
    //将environ做一个备份
    char **initialEnv = environ;
    //请求计数
    int count = 0;

    //阻塞点，只有请求到达的时候Accept才会返回
    while (FCGI_Accept() >= 0) {
        //获取环境变量 CONTENT_LENGTH 表示用户请求数据的长度
        //判断用户有没有请求数据
        char *contentLength = getenv("CONTENT_LENGTH");
        int len;

        //状态行，省略，nginx自动添加
        //响应头 \r\n 响应数据
        printf("Content-type: text/html\r\n"
                "\r\n"
                "<title>FastCGI echo</title>"
                "<h1>FastCGI echo</h1>\n"
                "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

        if (contentLength != NULL) {
            //strtoi  char * -> int   strtol char* -> long
            len = strtol(contentLength, NULL, 10);
        }
        else {
            len = 0;
        }

        if (len <= 0) {
            //没有数据从标准输入进来（没有用户数据）
            printf("No data from standard input.<p>\n");
        }
        else {
            int i, ch;
            

            //创见一个数组,存储用户发送过来的数据
            char *data =(char *)malloc(len);
            assert(data);

            printf("Standard input:<br>\n<pre>\n");
            for (i = 0; i < len; i++) {
                if ((ch = getchar()) < 0) {
                    printf("Error: Not enough bytes received on standard input<p>\n");
                    break;
                }
                //putchar(ch);
                //赋值data数组
                data[i] =ch;
            }
            printf("\n</pre><p>\n");


            char fileName[512]={0};
            char contentType[512]={0};
            char *ptrFileBegin=NULL;
            char *ptrFileEnd=NULL;

            //调用上传的函数，将各个参数以及文件数据抽离出来
            int ret = read_file(data,len,fileName,contentType,&ptrFileBegin,&ptrFileEnd);
            assert(ret==0);

            //将文件数据写到硬盘上
            int fd = open(fileName,O_CREAT|O_WRONLY,0664);
            assert(fd>0);
            write(fd , ptrFileBegin,ptrFileEnd - ptrFileBegin);
            close(fd);
            free(data);
        }

        PrintEnv("Request environment", environ);
        PrintEnv("Initial environment", initialEnv);
    } /* while */

    return 0;
}
                
int read_file(char *data , size_t len,
        char *out_file_name , char *out_content_type,
        char **out_ptrBegin, char **out_ptrEnd)
{
    char bound[512]={0};
    char *ptrBegin = data;
    char *ptrEnd = NULL;
    ptrEnd = strstr(data,"\r\n");
    assert(ptrEnd!=NULL);
    //将bound拷贝出来
    strncpy(bound,ptrBegin , ptrEnd - ptrBegin);
    printf("Get bound : %s\n</br>",bound);

    //以下很多步骤都需要判错

    //获取filename
    ptrBegin=strstr(ptrEnd+2,"filename=") + 10; //找到文件名的开始
    ptrEnd = strchr(ptrBegin,'\"'); //找到文件名的结束
    strncpy(out_file_name,ptrBegin,ptrEnd - ptrBegin);
    printf("Get filename : %s\n</br>",out_file_name);
    
    //获取content type
    ptrBegin = strstr(ptrEnd+2,"Content-Type: ")+strlen("Content-Type: ");
    ptrEnd = strstr(ptrBegin,"\r\n");
    strncpy(out_content_type,ptrBegin,ptrEnd-ptrBegin);
    printf("Get Content type  : %s\n</br>",out_content_type);

    //获取文件的开始和结束地址
    //通过查找 \r\n\r\n 来确定文件的开始位置
    ptrBegin = strstr(ptrEnd,"\r\n\r\n")+4;
    ptrEnd = memstr(ptrBegin,len-(ptrBegin-data),bound) -2 ; //回退两个字节，\r\n

    *out_ptrBegin= ptrBegin;
    *out_ptrEnd = ptrEnd;
    return 0;
}

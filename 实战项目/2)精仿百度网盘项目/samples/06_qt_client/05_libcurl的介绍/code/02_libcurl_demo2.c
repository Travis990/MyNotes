#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

typedef struct Test
{
	char buf[1024 * 4];
	int i;
}Test;

//此回调函数被调用的时机是有响应数据到达，这些数据由ptr指向，每次接收的数据大小是size*nmemb
size_t callback( char *ptr, size_t size, size_t nmemb, void *stream)
{
	Test *p = (Test *)stream;
	memcpy(p->buf + p->i, ptr, size*nmemb);
	p->i += size*nmemb;
	p->buf[p->i] = 0;
	
	return size*nmemb;
}

int main()
{
	CURL *curl = curl_easy_init();//初始化一个CURL的指针
	if(NULL == curl)  
    {  
        return CURLE_FAILED_INIT;  
    }  
	
	//设置 curl 的属性和操作
	//CURLOPT_URL：设置访问URL
	curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/login?type=10&user=测试&pwd=123456");
	
	//设置回调函数callback
	//callback将在libcurl接收到数据后被调用，因此函数多做数据保存的功能
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	Test obj;
	memset(&obj, 0, sizeof(obj) );
	
	//CURLOPT_WRITEDATA 传递指针给libcurl，该指针表明CURLOPT_HEADERFUNCTION函数的stream指针的来源
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&obj); //&obj -> stream
	
	
	//完成curl_easy_setopt指定的所有选项, 返回0意味一切ok，非0代表错误发生，此函数会阻塞，等待服务器返回数据
	CURLcode res = curl_easy_perform(curl);
	if(res == CURLE_OK)//成功
	{
		printf("buf = %s\n", obj.buf);
	}
	else
	{
		printf("err = %s\n", curl_easy_strerror(res) ); //打印出错原因
	}
	
	curl_easy_cleanup(curl);
	
	return 0;
}

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>


//此回调函数被调用的时机是有响应数据到达，这些数据由ptr指向，每次接收的数据大小是size*nmemb
size_t callback( char *ptr, size_t size, size_t nmemb, void *stream)
{
	return fwrite(ptr, size, nmemb, (FILE *)stream);  
}

//进度回调函数
static int progress(void *p,  
                    double dltotal, double dlnow,  
                    double ultotal, double ulnow)  
{   
	CURL *curl = (CURL *)p;
	printf("%lf %%\n",  (long)dlnow/dltotal*100);
	
	double totalTime = 0;  
    int res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totalTime);  
    if((CURLE_OK == res) && totalTime)
	{
		printf("耗时：%lf\n", totalTime);
	}
	
	return 0;
}  

int main()
{
	
	CURL *curl = curl_easy_init();//初始化一个CURL的指针
	if(NULL == curl)  
    {  
        return CURLE_FAILED_INIT;  
    }  
	
	FILE *fp = fopen("demo.mp3", "wb");
	if(fp == NULL)
	{
		perror("fopen");
		return -1;
	}
	
	//设置 curl 的属性和操作
	//CURLOPT_URL：设置访问URL
	curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.31.138:80/group1/M00/00/00/wKgfilh7DuWAC8hXAHaI63U30Yo403.mp3");
	
	//设置回调函数callback
	//callback将在libcurl接收到数据后被调用，因此函数多做数据保存的功能
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

	//CURLOPT_WRITEDATA 传递指针给libcurl，该指针表明CURLOPT_HEADERFUNCTION函数的stream指针的来源
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)fp); //&fp -> stream
	
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);//设为0才能设置进度响应函数

	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress);//进度回调函数  
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, curl);//存储数据结构体指针  
  
	
	//完成curl_easy_setopt指定的所有选项, 返回0意味一切ok，非0代表错误发生，此函数会阻塞，等待服务器返回数据
	CURLcode res = curl_easy_perform(curl);
	if(res == CURLE_OK)//成功
	{
		//printf("\n");
	}
	else
	{
		printf("err = %s\n", curl_easy_strerror(res) ); //打印出错原因
	}
	
	
	curl_easy_cleanup(curl);
	
	return 0;
}

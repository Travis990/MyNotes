#include <stdio.h>
#include "cJSON.h"
void creatJson()
{
	char *string =NULL;
	//创建一个对象，作为根对象
	cJSON *root = cJSON_CreateObject();
	if(!root)
	{
		printf("%s\n",cJSON_GetErrorPtr());
		return;
	}

	//正常添加
	cJSON *user = cJSON_CreateString("itcast");
	cJSON_AddItemToObject(root,"user",user);

	//使用宏的形式添加
    cJSON_AddStringToObject(root,"passwd","123456");
	string = cJSON_Print(root);
	printf("createJson : %s\n",string);
	free(string);
	//删除所有json对象
	cJSON_Delete(root);
}
void parseJson()
{
	const char *jsonStr = 
		"{\"user\":\"itcast\",\"passwd\":\"123456\"}";
	cJSON *obj = cJSON_Parse(jsonStr);
	if(!obj)
	{
		printf("%s\n",cJSON_GetErrorPtr());
		return;
	}
	cJSON *user = cJSON_GetObjectItem(obj,"user");
	if(!user)
	{
		printf("%s\n",cJSON_GetErrorPtr());
		return;
	}
	printf("parseJson : the user name is %s \n",user->valuestring);
	cJSON_Delete(obj);
}
int main()
{
	creatJson();
	parseJson();
	return 0;
}

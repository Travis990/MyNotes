#include <event.h>
#include <stdio.h>

int main()
{
    char ** methods = event_get_supported_methods();//获取libevent后端支持的方法
    int i =0;
    for(i = 0;methods[i] != NULL ;i++)
    {
        printf("%s\n",methods[i]);
    }
	struct event_base * base = event_base_new();
	printf("%s\n",event_base_get_method(base));

    return 0;
}

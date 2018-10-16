#include "make_log.h"//日志文件头文件

int main(int argc, char *argv[])
{
	char *p = "hello itcast";
    LOG("test_log", "test", "test info[%s]", p);//打印日志
  
	return 0;
}

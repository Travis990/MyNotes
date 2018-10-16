#include <sys/time.h>
#include <time.h>

//当前时间戳
struct timeval tv;
struct tm* ptm;
char time_str[128];

//使用函数gettimeofday()函数来得到时间。它的精度可以达到微妙
gettimeofday(&tv, NULL);
ptm = localtime(&tv.tv_sec);//把从1970-1-1零点零分到当前时间系统所偏移的秒数时间转换为本地时间
//strftime() 函数根据区域设置格式化本地时间/日期，函数的功能将时间格式化，或者说格式化一个时间字符串
strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", ptm);
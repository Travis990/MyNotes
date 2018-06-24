## 1) strstr() 函数实现
```
#include <stdio.h>
#include <stdlib.h>

char* _strstr(const char *, const char *); // 仿造 strstr()函数申明

void main() {
	char* str = "673008865@qq.com";
	printf("%s\n", _strstr(str, "qq"));
}

/* strstr()函数实现 */
char* _strstr(const char *_str, const char *_substr) {
	if (NULL == _str || NULL == _substr) {
		return -1;
	}
	while (*_str != 0)
	{
		if (*_str == *_substr) {
			int i = 0, // substr的循环次数
				index = 0; // 字符匹配的相同指数
			char *str = _str,
				*substr = _substr;
			while (*substr != 0)
			{
				if (*str == *substr) {
					index++;
				}
				str++;
				substr++;
				i++;
			}
			if (index == i) { // 如果指数等于循环次数则返回当前指针位置
				return _str;
			}
		}
		_str++;
	}
	return -1;
}
```
## 2) strcpy() 函数实现
```
#include <stdio.h>
#include <stdlib.h>

int _strcpy(char *, const char const *); // 仿造 strcpy()函数申明

void main() {
	char *str = "Hello World!";
	char str1[100];

	_strcpy(str1, str);
	printf("%s\n", str1);
}

/* strcpy() 函数实现 */
int _strcpy(char *_des, const char const *_source) {
	if ( NULL == _des || NULL == _source ) {
		return -1;
	}
	while (*_des++ = *_source++);
	return 0;
}
```
## 3) strcat() 函数实现
```
#include <stdio.h>
#include <stdlib.h>

int _strcat(char *, const char const *); // 仿造 strcat()函数申明

void main() {
	char *str = "World!";
	char str1[100] = "Hello ";

	_strcat(str1, str);
	printf("%s\n", str1);
}

/* strcat() 函数实现 */
int _strcat(char *_dest, const char const *_src) {
	if ( NULL == _dest || NULL == _src ) {
		return -1;
	}
	while (*_dest != 0) {
		_dest++;
	}
	while (*_dest++ = *_src++);
	return 0;
}
```

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <io.h>
using namespace std;

int glob(const char* pattern = "./*");

int main()
{
	//glob("F:/VS_Projects/md5sum/md5sum/*");
	glob();
	
	system("pause");
	return 0;
}

int glob(const char* pattern)
{
	const char *ptrEnd = strrchr(pattern,'/');
	const char *suffix_rule = ptrEnd;              // 尾缀规则 /* 或 /*.*
	const int cur_path_len = ptrEnd + 1 - pattern; // 取到字符串最后一个'/'的位置, 包含 '/'
	char *cur_path = new char[cur_path_len + 1];   // 创建字符存储空间, 包含 \0
	memset(cur_path, 0, cur_path_len + 1);         // 初始化空间0, 包含 \0
	strncpy(cur_path, pattern, cur_path_len);      // 拷贝数据
	//cout << cur_path <<endl;    // 当前遍历目录路径
	//cout << suffix_rule <<endl; // 尾缀规则

	long fh = 0;
	_finddata_t fileInfo;
	string pathName;

	if ((fh = _findfirst(pattern, &fileInfo)) == -1L) return -1;

	do
	{
		if ( (strcmp(fileInfo.name,".")!=0) && (strcmp(fileInfo.name, "..") != 0) )
		{
			if (fileInfo.attrib == _A_SUBDIR)
			{
				//cout << "DIR:" << string(cur_path) + fileInfo.name + suffix_rule << endl;
				glob( (string(cur_path) + fileInfo.name + suffix_rule).c_str() ); // 递归遍历子级目录
			}
			else
			{
				cout << string(cur_path) + fileInfo.name << endl;
			}
		}
	} while (_findnext(fh, &fileInfo) == 0);

	// 资源释放
	_findclose(fh);
	delete[] cur_path;

	return 0;
}
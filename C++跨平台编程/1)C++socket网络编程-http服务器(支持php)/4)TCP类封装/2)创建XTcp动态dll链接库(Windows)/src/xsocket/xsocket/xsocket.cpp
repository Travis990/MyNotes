// xsocket.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "xsocket.h"


// 这是导出变量的一个示例
XSOCKET_API int nxsocket=0;

// 这是导出函数的一个示例。
XSOCKET_API int fnxsocket(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 xsocket.h
Cxsocket::Cxsocket()
{
    return;
}

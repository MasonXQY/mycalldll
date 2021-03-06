// mycalldll.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
typedef int(*dllfun)(int,char**);  //定义形式对应的函数指针类型

int main()
{
	const char * location = ".\\";//输入WPS_cal_dir.txt路径，该txt中记录输入输出数据路径
	dllfun call_wps_dll; //声明一个函数指针
	HINSTANCE hdll;
	//hdll = LoadLibrary(TEXT("D:\\FangCloudSync\\Dropbox\\Github\\mycalldll\\mycalldll\\WPS.dll"));
	hdll = LoadLibrary("WPS.dll");//输入dll文件地址
	if (hdll == NULL)
	{
		printf("无法载入dll\n");
		FreeLibrary(hdll);
		getchar();
		return 0;
	}
	call_wps_dll = (dllfun)GetProcAddress(hdll, "wpsmain");
	if (call_wps_dll == NULL)
	{
		printf("无法获取函数地址\n");
		FreeLibrary(hdll);
		getchar();
		return 0;
	}

	char * argv[1];
	argv[0] = (char*)location;
	call_wps_dll(1, argv);//调用wps.dll进行风电出力模拟计算
	FreeLibrary(hdll);
	getchar();
	return 1;
}


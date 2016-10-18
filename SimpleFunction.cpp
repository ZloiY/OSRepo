// SimpleFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Point.h"
#include <Windows.h>
#include <time.h>
#include <chrono>
#include <string>
#include <mutex>
#include <cmath>

#define BUF_SIZE sizeof(Point)
TCHAR szName[] = TEXT("Global\MyFileMappingObject");
using namespace std;
double calcFunction(double);
chrono::milliseconds currentMilis();
int main()
{	
	LPCTSTR pBuf;
	HANDLE hMapFile;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION valuePi;
	HANDLE event1 = CreateEvent(NULL, FALSE, FALSE, L"event1");
	//HANDLE mutex = CreateMutex(NULL, FALSE, L"test");
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BUF_SIZE,
		szName);
	if (hMapFile == NULL) {
		_tprintf(TEXT("Could not create file mapping object(%d).\n"),
			GetLastError());
		return 1;
	}
	int x = 0;
	while (x <= 15) {
		Point point = Point();
		point.setX(x);
		int res = calcFunction(x++);
		chrono::milliseconds ms;
		ms = currentMilis();
		point.setTimeCalc(ms.count());
		point.setY(res);
		point.getTimeCalc();
		pBuf = (LPTSTR)MapViewOfFile(hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			BUF_SIZE);
		if (pBuf == NULL) {
			_tprintf(TEXT("Could not map view of file(%d).\n"),
				GetLastError());
			CloseHandle(hMapFile);
			return 1;
		}
		CopyMemory((PVOID)pBuf, &point, sizeof(Point));
		UnmapViewOfFile(pBuf);
		CreateProcess(L"C:\\Users\\ZloiY\\Documents\\Visual Studio 2015\\Projects\\PointValue\\Debug\\PointValue.exe", NULL, NULL, NULL, FALSE,
			NULL, NULL, NULL, &cif, &valuePi);
		if (WaitForSingleObject(event1, INFINITE) != WAIT_OBJECT_0) return 1;
	}
	CloseHandle(hMapFile);
	CloseHandle(event1);
    return 0;
}

double calcFunction(double x) {
	return sqrt(x);
}

chrono::milliseconds currentMilis() {
	return chrono::duration_cast< chrono::milliseconds >(
		chrono::system_clock::now().time_since_epoch()
		);
}

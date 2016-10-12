// SimpleFunction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "Point.h"
#include <cstdlib>
#include <Windows.h>
#include <time.h>
#include <ratio>
#include <chrono>
#include <iostream>
#include <string>
#include <mutex>
#include <cmath>

#define BUF_SIZE 256
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
	PROCESS_INFORMATION functioPi;
	PROCESS_INFORMATION logPi;
	PROCESS_INFORMATION valuePi;
	HANDLE mutex = CreateMutex(NULL, FALSE, L"test");
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
	while (x < 3) {
		if (WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0) {
			Point point = Point();
			point.setX(x);
			int res = calcFunction(x++);
			chrono::milliseconds ms;
			ms = currentMilis();
			//cout << ms.count();
			point.setTimeCalc(ms.count());
			point.setY(res);
			point.getTimeCalc();
			//cout << point.getX() << " " << point.getY() << " "  << " \n\n";
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
			CreateProcess(L"C:\\Users\\ZloiY\\Documents\\Visual Studio 2015\\Projects\\PointLog\\Debug\\Pointlog.exe", NULL, NULL, NULL, FALSE,
				NULL, NULL, NULL, &cif, &logPi);
			ReleaseMutex(mutex);
		}
	}
	CloseHandle(mutex);
	CloseHandle(hMapFile);
	TerminateProcess(valuePi.hProcess, NO_ERROR);
	TerminateProcess(logPi.hProcess, NO_ERROR);
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

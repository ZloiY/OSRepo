// PointLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Point.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <time.h>
#pragma comment(lib, "user32.lib")

#define BUF_SIZE sizeof(Point)
HANDLE event2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"event2");
TCHAR szName[] = TEXT("Global\MyFileMappingObject");
using namespace std;
chrono::milliseconds currentMilis();
std::string convert(LPCSTR str) {
	return std::string(str);
}
int main()
{
	LPCTSTR pBuf;
	HANDLE hMapFile;
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		szName);
	if (hMapFile == NULL) {
		_tprintf(TEXT("Could not open file mapping object in point log(%d).\n"),
			GetLastError());
		return 1;
	}
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
	Point point = Point();
	CopyMemory(&point, (PVOID)pBuf, sizeof(Point));
	ofstream pointLog("E:\\Log.txt", ios::app);
	if (pointLog.is_open()) {
		pointLog << point.getTimeCalc() << " " << point.getTimeWrite() << endl;
		pointLog.close();
	}
	else cout << "File unable to open.\n";
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	SetEvent(event2);
	CloseHandle(event2);
    return 0;
}

chrono::milliseconds currentMilis() {
	return chrono::duration_cast< chrono::milliseconds >(
		chrono::system_clock::now().time_since_epoch()
		);
}
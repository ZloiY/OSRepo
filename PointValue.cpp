// PointValue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include <time.h>
#include "point.h"
#pragma comment(lib, "user32.lib")
using namespace std;
TCHAR szName[] = TEXT("Global\MyFileMappingObject");
chrono::milliseconds currentMilis();
int main()
{
	HANDLE event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"event1");
	HANDLE event2 = CreateEvent(NULL, FALSE, FALSE, L"event2");
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION logPi;
	LPCTSTR pBuf;
	HANDLE hMapFile;
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		szName);
	if (hMapFile == NULL) {
		_tprintf(TEXT("Could not open file mapping object val (%d).\n"),
			GetLastError());
		return 1;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(Point));
	if (pBuf == NULL) {
		_tprintf(TEXT("Could not map view of file(%d).\n"),
			GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}
	Point point = Point();
	CopyMemory(&point, (PVOID)pBuf, sizeof(Point));
	ofstream file = ofstream("E:\\calc.txt", ios::app);
	chrono::milliseconds time;
	if (file.is_open()) {
		file << point.getX() << " " << point.getY() << endl;
		time = currentMilis();
		point.setTimeWrite(time.count());
		point.getTimeWrite();
		file.close();
	}
	else cout << "File unable to open\n";
	CopyMemory((PVOID)pBuf, &point, sizeof(Point));
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	CreateProcess(L"C:\\Users\\ZloiY\\Documents\\Visual Studio 2015\\Projects\\PointLog\\Debug\\Pointlog.exe", NULL, NULL, NULL, FALSE,
		NULL, NULL, NULL, &cif, &logPi);
	if (WaitForSingleObject(event2, INFINITE) == WAIT_OBJECT_0) {
		SetEvent(event1);
		CloseHandle(event1);
		CloseHandle(event2);
		return 0;
	}
	else return 1;
}

chrono::milliseconds currentMilis() {
	return chrono::duration_cast< chrono::milliseconds >(
		chrono::system_clock::now().time_since_epoch()
		);
}
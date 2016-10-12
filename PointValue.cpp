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
	HANDLE mutex = OpenMutex(SYNCHRONIZE, FALSE, L"test");
	if (WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0) {
		LPCTSTR pBuf;
		HANDLE hMapFile;
		hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
			FALSE,
			szName);
		if(hMapFile==NULL) {
			_tprintf(TEXT("Could not open file mapping object(%d).\n"),
				GetLastError());
			return 1;
		}
		pBuf = (LPTSTR)MapViewOfFile(hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			256);
		if (pBuf == NULL) {
			_tprintf(TEXT("Could not map view of file(%d).\n"),
				GetLastError());
			CloseHandle(hMapFile);
			return 1;
		}
		Point point = Point();
		CopyMemory(&point, (PVOID)pBuf, sizeof(Point));
		//cout << point.getX() << " " << point.getY() << " " << point.getTimeCalc() << endl;
		ofstream file = ofstream("E:\\calc.txt",ios::app);
		chrono::milliseconds time;
		if (file.is_open()) {
			file << point.getX() << " " << point.getY() << endl;
			time = currentMilis();
			//cout << time.count() << endl;
			point.setTimeWrite(time.count());
			file.close();
		}
		else cout << "File unable to open\n";
		//cout << endl;
		CopyMemory((PVOID)pBuf, &point, sizeof(Point));
		UnmapViewOfFile(pBuf);
		ReleaseMutex(mutex);
		CloseHandle(hMapFile);
	}
	CloseHandle(mutex);
    return 0;
}

chrono::milliseconds currentMilis() {
	return chrono::duration_cast< chrono::milliseconds >(
		chrono::system_clock::now().time_since_epoch()
		);
}
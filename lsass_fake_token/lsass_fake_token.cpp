#include "stdafx.h"
#include <windows.h>
#include <psapi.h>
#include <string>

#define __USERNAME__ L"FakeForestAdmin"
#define __DOMAIN__   L"FakeDomain"
#define __PASSWORD__ L"YesThisIsAFakePassword"

void StartChildProcess() {
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO         si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	LPWSTR fn = new TCHAR[MAX_PATH];
	GetModuleFileName(NULL, fn, MAX_PATH - 2);

	std::wstring tmp(fn);
	tmp.append(L" 1");
	LPWSTR _fn = const_cast<LPWSTR>(tmp.c_str());

	CreateProcessWithLogonW(__USERNAME__, __DOMAIN__, __PASSWORD__, LOGON_NETCREDENTIALS_ONLY, NULL, _fn, NULL, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
		if (_tcscmp(argv[1], L"1") == 0)
			while (true)
				Sleep(3600000);

	Sleep(30000);
	StartChildProcess();

	return 0;
}


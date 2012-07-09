// ReNameTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;
#include<windows.h>
#include <tchar.h>
#include <strsafe.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	TCHAR szDir[MAX_PATH];

	StringCchCopy(szDir, MAX_PATH, _T("E:\\Video\\wwdc20122\\*"));
	_tprintf (TEXT("Target file is %s\n"), szDir);
	hFind = FindFirstFile(szDir, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
	{
		printf ("FindFirstFile failed (%d)\n", GetLastError());
		return 1;
	} 
	int nRet;
	TCHAR szNewFile[MAX_PATH];
	TCHAR szOldFile[MAX_PATH];
	while((nRet=FindNextFile(hFind, &FindFileData)) != 0)
	{
		_tprintf (TEXT("%s\n"),  FindFileData.cFileName);
		StringCchCopy(szNewFile, MAX_PATH,_T("E:\\Video\\wwdc20122\\"));
		StringCchCopy(szOldFile, MAX_PATH,_T("E:\\Video\\wwdc20122\\"));
		StringCchCat(szNewFile, MAX_PATH, FindFileData.cFileName);
		StringCchCat(szOldFile, MAX_PATH, FindFileData.cFileName);
		size_t iLen = 0;
		StringCchLength(szNewFile, MAX_PATH, &iLen);
		for (int i=0; i<(int)iLen; i++)
		{
			if(szNewFile[i] == '_')
			{
				szNewFile[i] = '\0';
				StringCchCat(szNewFile, MAX_PATH, TEXT(".mp3"));
				_tprintf (TEXT("%s\n"),  szNewFile);
		
				int result = _wrename( szOldFile, szNewFile);
				if( result != 0 )
					printf( "Could not rename \n" );
				break;
			}
		}
	}

	FindClose(hFind);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//
//	LOGFILE.CPP : Text file log
//
// Copyright(c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "logfile.h"
#include <time.h>

/////////////////////////////////////////////////////////////////////////////
LogFile::LogFile()
		: hFile(INVALID_HANDLE_VALUE)
{
}

/////////////////////////////////////////////////////////////////////////////
LogFile::~LogFile()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
bool LogFile::open(LPCTSTR filename)
{
	DWORD flags = GENERIC_READ | GENERIC_WRITE, disp = OPEN_ALWAYS;
	DWORD attr = FILE_ATTRIBUTE_NORMAL;

	close();

	hFile = CreateFile(filename, flags, FILE_SHARE_READ|FILE_SHARE_WRITE,
	                   NULL, disp, attr, NULL);

	return hFile != INVALID_HANDLE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////
void LogFile::close()
{
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool LogFile::log(LPCTSTR fmt, ...)
{
	CString message, entry;

	va_list argList;
	va_start(argList, fmt);
	message.FormatV(fmt, argList);
	va_end(argList);

	CTime tm = CTime::GetCurrentTime();
	entry.Format(_T("%s\t%s\r\n"),
	             tm.Format(_T("%m/%d/%Y %H:%M:%S")),
	             message);

	DWORD toWrite = entry.GetLength() * sizeof(TCHAR), written[1];
	WriteFile(hFile, entry, toWrite, written, NULL);

	return written[0] == toWrite;
}
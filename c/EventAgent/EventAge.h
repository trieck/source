//////////////////////////////
//	Module:	EVENTAGE.H		//
//	Author: Thomas A. Rieck	//
//	Date:	05/16/1997		//
//////////////////////////////

#ifndef LOGFILE
#define	LOGFILE "error.log"
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <mapi.h>

typedef struct tagEVENTRECORD {
	DWORD	EventID;
	TCHAR	szEventDate[128];
	TCHAR	szEventType[50];
	TCHAR	szSourceName[255];
	TCHAR	szComputerName[255];
	WORD	numStrings;
	LPCSTR	pStrings[255];
	TCHAR	pMessage[1024];
} EVENTRECORD;

void	main (void);
void	GetEventType(LPWORD pEventType, LPSTR szEventType);
void	SetEventRecord(EVENTLOGRECORD* pEventLogRecord, EVENTRECORD* pER);
void	GetCurrentDate (LPSTR szDate);
void	ConvertUTCToDate(DWORD dwUTC, LPSTR szDate);
void	ShowError(void);
DWORD	GetFilePath(LPSTR szFilePath);
DWORD	GetEventMessageFileName(LPCSTR szSourceName, LPSTR szMessageFileName);
DWORD	GetEventMessage(DWORD dwEventID, LPCSTR szMessageFileName, LPCSTR pStrings[], LPSTR pMessage);
BOOL	ShouldWriteRecord(DWORD dwWrittenTime);
DWORD	SendMail();
DWORD	GetLogonInfo(LPSTR lpszMailProfile, LPSTR lpszPassword);
DWORD	GetRecipients(LPSTR lpszRecipient);

#endif	// LOGFILE
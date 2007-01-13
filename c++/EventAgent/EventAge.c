//////////////////////////////
//	Module:	EVENTAGE.C		//
//	Author: Thomas A. Rieck	//
//	Date:	05/16/1997		//
//////////////////////////////

#include "EventAge.h"

CHAR szFileName[_MAX_PATH + _MAX_FNAME];

void main()
{
	HANDLE			hEventLog;
	EVENTLOGRECORD* pEventLogRecord = 0;
	EVENTRECORD*	pER = 0;
	CHAR			szFilePath[_MAX_PATH];
	CHAR			szDate[9];
	DWORD			dwBytesRead, dwBytesNeeded;
	DWORD			dwEventLogRecords, dwTemp;
	FILE*			fp;
	
	// get current date
	GetCurrentDate(szDate);

	// get file path
	if (!(GetFilePath(szFilePath)))
		strcpy(szFilePath, "");

	// format file name
	sprintf(szFileName, "%s%s%s", szFilePath, szDate, ".LOG");

	// open security event log on local machine
	printf("Opening Security Event Log for Reading...\n");
	if (!(hEventLog = OpenEventLog(NULL, "Security")))
	{
		printf("Error Opening Event Log.\n");
		return;
	}
		
	// open event file
	printf("Opening Event File %s for Writing...\n", szFileName);
	if ((fp = fopen(szFileName, "w+t")) == NULL)
	{
		printf("Error Opening Event File.\n");
		return;
	}
						
	// find the number of event log records
	GetNumberOfEventLogRecords(hEventLog, &dwEventLogRecords);

	// read data and output to file
	printf("Writing Data To File...\n");

	for (dwTemp = 1; dwTemp <= dwEventLogRecords; dwTemp++)
	{
		if (!(pEventLogRecord = (EVENTLOGRECORD*)malloc(16384)))
			return;

		// read records from event log
		if (!(ReadEventLog(hEventLog,		// event log handle
				EVENTLOG_SEEK_READ |
				EVENTLOG_FORWARDS_READ,		// get specified record
				dwTemp,
				pEventLogRecord,			// buffer address
				16384,						// max size
				&dwBytesRead,				// number of bytes read
				&dwBytesNeeded)))			// number of bytes needed
			ShowError();
		
		// read record information
		if (dwBytesRead)
		{
			if (ShouldWriteRecord(pEventLogRecord->TimeWritten))
			{
				// allocate memory for event record
				if (!(pER = (EVENTRECORD*)malloc(sizeof(EVENTRECORD))))
				{
					printf("Error allocating memory for record.\n");
					if (pEventLogRecord) free (pEventLogRecord);
					return;
				}

				// set event record into structure
				SetEventRecord(pEventLogRecord, pER);
		
				// write data to file
				fprintf(fp, "%d\t%s\t%s\t%s\t%s\n%s\n", pER->EventID, pER->szEventDate,
					pER->szEventType, pER->szSourceName, pER->szComputerName,
					pER->pMessage);

				// free allocated memory
				if (pER) free(pER);
			}
		}
		// free allocated buffer
		if (pEventLogRecord) free (pEventLogRecord);
	}

	printf("Closing Files...\n");

	// release event log handle
	CloseEventLog(hEventLog);

	// close event file
	_flushall();
	fclose(fp);
	
	// send message
	printf("Sending messages...\n");
	SendMail();
}

void SetEventRecord(EVENTLOGRECORD* pEventLogRecord, EVENTRECORD* pER)
{
	LPCSTR	pStringOffset;
	LPSTR	pOffset;
	CHAR	szMessageFileName[_MAX_FNAME];
	WORD	i;

	// set event id
	pER->EventID = pEventLogRecord->EventID;

	// set event date
	ConvertUTCToDate(pEventLogRecord->TimeWritten, pER->szEventDate);

	// set event type
	GetEventType(&pEventLogRecord->EventType, pER->szEventType);

	// set source name
	pOffset	= (LPSTR)pEventLogRecord + sizeof(EVENTLOGRECORD);
	strcpy(pER->szSourceName, pOffset);
	
	// set computer name
	pOffset += strlen(pER->szSourceName) + 1;
	strcpy(pER->szComputerName, pOffset);

	// get number of strings
	pER->numStrings = pEventLogRecord->NumStrings;
	
	// get insert strings
	pStringOffset	= (LPCSTR)pEventLogRecord + pEventLogRecord->StringOffset;
	pOffset			= (LPSTR)pStringOffset;
	
	for (i = 0; i < pER->numStrings; i++)
	{
		pER->pStrings[i] = (LPCSTR)pOffset;
		pOffset = strchr(pOffset, '\0') + 1;
	}
		
	// get event message filename
	if (GetEventMessageFileName(pER->szSourceName, szMessageFileName))
		// get event message
		GetEventMessage(pER->EventID, szMessageFileName, pER->pStrings, pER->pMessage);
	else
		// set empty message
		strcpy(pER->pMessage, "");
}	
void GetEventType(LPWORD pEventType, LPSTR szEventType)
{
	switch(*pEventType)
	{
	case EVENTLOG_ERROR_TYPE:
		strcpy(szEventType, "Error");
		break;
	case EVENTLOG_WARNING_TYPE:
		strcpy(szEventType, "Warning");
		break;
	case EVENTLOG_INFORMATION_TYPE:
		strcpy(szEventType, "Information");
		break;
	case EVENTLOG_AUDIT_SUCCESS:
		strcpy(szEventType, "Audit Success");
		break;
	case EVENTLOG_AUDIT_FAILURE:
		strcpy(szEventType, "Audit Failure");
		break;
	default:
		strcpy(szEventType, NULL);
	}
}

void GetCurrentDate(LPSTR szDate)
{
	struct tm* pTime;
	time_t long_time;

	// converts date to string format - MMDDYY
	
	// set time zone from TZ environment variable. If TZ is not set,
    // the operating system is queried to obtain the default value 
    // for the variable. 
    _tzset();

	// get time as long integer
    time(&long_time);               
	
	// convert to local time
    pTime = localtime(&long_time); 
	
	// format date string 
	strftime(szDate, 9, "%m%d%y", pTime);
}

DWORD GetFilePath(LPSTR szFilePath)
{
	HKEY hKey;
	LPCSTR szRegPath = "SOFTWARE\\EventAgent\\Log";
	DWORD dwType, dwBytes;
	CHAR szBuffer[_MAX_PATH];

	// open registry
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegPath, 0,
			KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
	{
		ShowError();
		return (0);
	}
	else
	{
		if (RegQueryValueEx(hKey, "FilePath", 0, &dwType,
			szBuffer, &dwBytes) != ERROR_SUCCESS)
		{
			ShowError();
			RegCloseKey(hKey);
			return(0);
		}
	}
	strncpy(szFilePath, szBuffer, dwBytes);
	RegCloseKey(hKey);
	return (1);
}

void ConvertUTCToDate(DWORD dwUTC, LPSTR szDate)
{	
	CHAR tmpbuff[128];
	LPSTR pTemp;
	
	strcpy(tmpbuff, ctime(&dwUTC));

	// search for newline character
	// if found replace with null
	if (pTemp = strchr(tmpbuff, '\n'))
		strcpy(pTemp, "\0");
		
	strcpy(szDate, tmpbuff);
}

BOOL ShouldWriteRecord(DWORD dwWrittenTime)
{
	CHAR tmpbuff[9], tmpbuff2[9];
	struct tm* pTime;

	// get current date
	_strdate(tmpbuff);

	// convert UTC time to date format
	pTime = localtime(&dwWrittenTime);
	strftime(tmpbuff2, 9, "%m/%d/%y", pTime);

	// compare strings
	return((strcmp(tmpbuff, tmpbuff2) == 0) 
			? TRUE : FALSE);
}

DWORD GetEventMessageFileName(LPCSTR szSourceName, LPSTR szMessageFileName)
{
	HKEY	hKey;
	DWORD	dwType, dwBytes;
	LPSTR	lpszBuffer;
	LPSTR	lpszBufferQry;
	LPCSTR	szRegPath	= "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Security\\";
	LPCSTR	szValue		= "EventMessageFile";

	// allocate buffers
	if (!(lpszBuffer	= malloc(_MAX_PATH + _MAX_FNAME)))
		return (0);

	if (!(lpszBufferQry	= malloc(_MAX_PATH + _MAX_FNAME)))
	{
		free(lpszBuffer);
		return (0);
	}
		
	sprintf(lpszBuffer, "%s%s", szRegPath, szSourceName);

	// open registry
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpszBuffer, 0,
			KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
	{
		free(lpszBuffer);
		free(lpszBufferQry);
		ShowError();
		return (0);
	}
	else
	{	// query value
		if ((RegQueryValueEx(hKey, szValue, 0, &dwType,
			lpszBufferQry, &dwBytes)) != ERROR_SUCCESS)
		{
			free(lpszBuffer);
			free(lpszBufferQry);
			ShowError();
			RegCloseKey(hKey);
			return(0);
		}
	}
	//expand environment strings
	ExpandEnvironmentStrings(lpszBufferQry, szMessageFileName, _MAX_PATH + _MAX_FNAME);
	
	RegCloseKey(hKey);

	// free allocated buffers
	free(lpszBuffer);
	free(lpszBufferQry);
	
	return (dwBytes);
}

DWORD GetEventMessage(DWORD dwEventID, LPCSTR szMessageFileName, LPCSTR pStrings[], LPSTR pMessage)
{
	HINSTANCE	hInstance;
	LPVOID		szBuffer;
	DWORD		dwTemp;

	// load resource library
	if (!(hInstance = LoadLibraryEx(
				TEXT(szMessageFileName),
				NULL,
				LOAD_LIBRARY_AS_DATAFILE)))
		return (0);

	// format message table entry
	dwTemp = FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_HMODULE |
				FORMAT_MESSAGE_ARGUMENT_ARRAY,
				hInstance,
				dwEventID,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&szBuffer,
				0,
				(va_list*)pStrings);

	if (dwTemp)
		strcpy(pMessage, szBuffer);

	// free allocated memory
	LocalFree(szBuffer);

	// free library
	FreeLibrary(hInstance);
}

DWORD SendMail()
{
	LHANDLE lhSession;
	HMODULE hModule;
	FARPROC fpMAPILogon, 
			fpMAPIResolveName,
			fpMAPISendMail, 
			fpMAPILogoff,
			fpMAPIFree;
	
	LPSTR	lpszMailProfile;
	LPSTR	lpszPassword;
	LPSTR	lpszRecipient;

	lpMapiRecipDesc pRecipDesc;
	MapiMessage		mm;
	MapiFileDesc	mfd;

	// allocate buffers
	if (!(lpszMailProfile = malloc(255)))
		return (0);
	if (!(lpszPassword = malloc(255)))
	{
		free(lpszMailProfile);
		return (0);
	}
	if (!(lpszRecipient = malloc(255)))
	{
		free(lpszMailProfile);
		free(lpszPassword);
	}

	// load MAPI library
	if (!(hModule = LoadLibrary("mapi32.dll")))
	{
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		return (0);
	}

	// get mail profile name and password
	if (!(GetLogonInfo(lpszMailProfile, lpszPassword)))
	{
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		return (0);
	}

	// get recipients
	if (!(GetRecipients(lpszRecipient)))
	{		
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		return (0);
	}
	// resolve DLL addresses
	fpMAPILogon			= GetProcAddress(hModule, "MAPILogon");
	fpMAPIResolveName	= GetProcAddress(hModule, "MAPIResolveName");
	fpMAPISendMail		= GetProcAddress(hModule, "MAPISendMail");
	fpMAPIFree			= GetProcAddress(hModule, "MAPIFreeBuffer");
	fpMAPILogoff		= GetProcAddress(hModule, "MAPILogoff");

	// logon to MAPI session
	if (((fpMAPILogon)(0, lpszMailProfile, lpszPassword, MAPI_DIALOG |
		MAPI_NEW_SESSION | MAPI_LOGON_UI, 0, &lhSession))
		!= SUCCESS_SUCCESS)
	{
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		FreeLibrary(hModule);
		return (0);
	}

	// resolve mail profile name
	if (((fpMAPIResolveName)(lhSession, 0, lpszRecipient, MAPI_DIALOG,
		0, &pRecipDesc)) != SUCCESS_SUCCESS)
	{
		(fpMAPILogoff)(lhSession,0,0,0);
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		FreeLibrary(hModule);
		return (0);
	}

	// prepare the files
	mfd.ulReserved			= 0;
	mfd.flFlags				= 0;
	mfd.nPosition			= -1;
	mfd.lpszPathName		= szFileName;
	mfd.lpszFileName		= NULL;
	mfd.lpFileType			= NULL;
	
	// prepare the message
	mm.ulReserved			= 0;
	mm.lpszSubject			= "Windows NT Event Log";
	mm.lpszNoteText			= NULL;
	mm.lpszMessageType		= NULL;
	mm.lpszDateReceived		= NULL;
	mm.lpszConversationID	= NULL;
	mm.flFlags				= 0;
	mm.lpOriginator			= NULL;
	mm.nRecipCount			= 1;
	mm.lpRecips				= pRecipDesc;
	mm.nFileCount			= 1;
	mm.lpFiles				= &mfd;
	
	// send the message
	if (((fpMAPISendMail)(lhSession, 0, &mm, 0, 0)) != SUCCESS_SUCCESS)
	{
		(fpMAPIFree)(pRecipDesc);
		(fpMAPILogoff)(lhSession,0,0,0);
		free(lpszMailProfile);
		free(lpszPassword);
		free(lpszRecipient);
		FreeLibrary(hModule);
		return(0);
	}

	// free allocated buffers
	(fpMAPIFree)(pRecipDesc);
	free(lpszMailProfile);
	free(lpszPassword);
	free(lpszRecipient);
		
	// logoff MAPI session
	(fpMAPILogoff)(lhSession,0,0,0);

	// free MAPI library
	FreeLibrary(hModule);

	return (1);
}

DWORD GetLogonInfo(LPSTR szMailProfile, LPSTR szPassword)
{
	HKEY hKey;
	LPCSTR	lpszRegPath			= "SOFTWARE\\EventAgent\\Messaging";
	LPCSTR	lpszLogonValue		= "LogonAccount";
	LPCSTR	lpszPasswordValue	= "Password";
	DWORD	dwType, dwBytes;
	CHAR	szBuffer[255];

	// open registry
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpszRegPath, 0,
		KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
	{
		ShowError();
		return (0);
	}
	else
	{
		// read mail profile
		if (RegQueryValueEx(hKey, lpszLogonValue, 0, &dwType,
			szBuffer, &dwBytes) != ERROR_SUCCESS)
		{
			ShowError();
			RegCloseKey(hKey);
			return(0);
		}
		strncpy(szMailProfile, szBuffer, dwBytes);
				
		// read password
		if (RegQueryValueEx(hKey, lpszPasswordValue, 0, &dwType,
			szBuffer, &dwBytes) != ERROR_SUCCESS)
		{
			ShowError();
			RegCloseKey(hKey);
			return(0);
		}
		strncpy(szPassword, szBuffer, dwBytes);
	}		

	RegCloseKey(hKey);
	return (1);
}

DWORD GetRecipients(LPSTR lpszRecipient)
{
	HKEY hKey;
	LPCSTR	lpszRegPath			= "SOFTWARE\\EventAgent\\Messaging";

	LPCSTR	lpszRecipientValue = "Recipient";
	CHAR	szBuffer[255];
	DWORD	dwType, dwBytes;
	
	// open registry
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpszRegPath, 0,
		KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
	{
		ShowError();
		return (0);
	}
	else
	{
		// read recipient
		if (RegQueryValueEx(hKey, lpszRecipientValue, 0, &dwType,
			szBuffer, &dwBytes) != ERROR_SUCCESS)
		{
			ShowError();
			RegCloseKey(hKey);
			return (0);
		}
		strncpy(lpszRecipient, szBuffer, dwBytes);
	}
	RegCloseKey(hKey);
	return (1);
}

void ShowError()
{
	LPVOID	lpMsgBuf;
	FILE*	fp;
	CHAR	szDate[7];

	if ((fp = fopen(LOGFILE, "a+t")) == NULL)
		return;
	
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);

	// display the string.
	printf(lpMsgBuf);

	// write string to log file
	GetCurrentDate(szDate);
	fprintf(fp, "%s - %s", szDate, lpMsgBuf);

	// Free the buffer.
	LocalFree(lpMsgBuf);

	// close file
	_flushall();
	fclose(fp);
}
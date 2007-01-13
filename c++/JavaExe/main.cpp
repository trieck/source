/////////////////////////////////////////////////////////////////////////////
//
//	MAIN.CPP : main entry point
//
//	Copyright(c) 2001, Thomas A. Rieck, All Rights Reserved
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	PROCESS_INFORMATION pi; 
	STARTUPINFO si; 
 
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si, sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO); 
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	BOOL retcode = CreateProcess(NULL,				
      "java.exe com.knowx.kxtrieck.JDBLib",			
      NULL,         
      NULL,         
      TRUE,         
      0,            
      NULL,         
      NULL,         
      &si,			
      &pi);			

	if (!retcode)
		return 1;	// failed to spawn

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	
	return 0;
}
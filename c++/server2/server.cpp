
// server.cpp

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500			// Windows 2000 stuff

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

static DWORD WINAPI ThreadProc(LPVOID lpParameter);

// main entry point

int _tmain(int argc, TCHAR *argv[])
{
    if (argc < 2)
        return 1;

    if (!QueueUserWorkItem(ThreadProc, argv[1], WT_EXECUTEDEFAULT))
        return 1;

    Sleep(INFINITE);

    return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    int sock = atoi((LPCTSTR)lpParameter);

    return 0;
}

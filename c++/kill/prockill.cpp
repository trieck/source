/////////////////////////////////////////////////////////////////////////////
//
//	PROCKILL.CPP : NT process killer
//

#include "common.h"
#include "prockill.h"

/////////////////////////////////////////////////////////////////////////////
ProcessKiller::ProcessKiller()
{
	// open token
	if (!OpenProcessToken(GetCurrentProcess(),
	                      TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		throw Exception(_T("Unable to open process token."));
	}

	// enable privileges
	if (!enablePrivileges()) {
		throw Exception(_T("Unable to enable privileges."));
	}
}

/////////////////////////////////////////////////////////////////////////////
ProcessKiller::~ProcessKiller()
{
	if (hToken) {
		CloseHandle(hToken);
	}
}

/////////////////////////////////////////////////////////////////////////////
void ProcessKiller::kill(const PidVector &pids, ostream *pstream)
{
	PidVector::const_iterator it = pids.begin();

	for ( ; it != pids.end(); it++) {
		kill(*it, pstream);
	}
}

/////////////////////////////////////////////////////////////////////////////
void ProcessKiller::kill(DWORD pid, ostream *pstream)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hProcess == NULL) {
		throw Exception(_T("Unable to open process."));
	}

	BOOL rtn = TerminateProcess(hProcess, 1);

	CloseHandle(hProcess);

	if (!rtn)
		throw Exception(_T("Unable to terminate process."));

	if (pstream != NULL)
		*pstream << _T("Process ID : ") << pid << _T(" terminated.") << endl;
}

/////////////////////////////////////////////////////////////////////////////
bool ProcessKiller::enablePrivileges()
{
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

	return (GetLastError() == ERROR_SUCCESS);
}


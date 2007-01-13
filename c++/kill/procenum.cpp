/////////////////////////////////////////////////////////////////////////////
//
//	PROCENUM.CPP : NT process enumerator
//

#include "common.h"
#include "procenum.h"

/////////////////////////////////////////////////////////////////////////////
ProcessEnumerator::ProcessEnumerator()
 : hModule(NULL)
{
	hModule = LoadLibrary(_T("PSAPI"));
	if (hModule == NULL)
		throw Exception(_T("Unable to load PSAPI library."));

	EnumProcesses = (EnumProcessesProc)GetProcAddress(hModule, 
		_T("EnumProcesses"));
	EnumProcessModules = (EnumProcessModulesProc)GetProcAddress(hModule, 
		_T("EnumProcessModules"));
	GetModuleBaseName = (GetModuleBaseNameProc)GetProcAddress(hModule,
		_TPROCNAME(GetModuleBaseName));
	GetModuleFileNameEx = (GetModuleFileNameExProc)GetProcAddress(hModule,
		_TPROCNAME(GetModuleFileNameEx));

	if (!EnumProcesses || !EnumProcessModules ||
		!GetModuleBaseName || !GetModuleFileNameEx)
		throw Exception(_T("Unable to locate procedure."));

	enumerate();
}

/////////////////////////////////////////////////////////////////////////////
ProcessEnumerator::~ProcessEnumerator()
{
	if (hModule != NULL) {
		FreeLibrary(hModule);
		hModule = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void ProcessEnumerator::enumerate()
{
	DWORD ids[maxpids];

	DWORD needed, entries;
	BOOL rtn = (*EnumProcesses)(ids, sizeof(ids), &needed);
	if (!rtn)
		throw Exception(_T("Process enumeration failed."));

	entries = needed / sizeof(DWORD);
	pids.reserve(entries);
	for (int i = 0; i < entries; i++)
		pids.push_back(ids[i]);
}

/////////////////////////////////////////////////////////////////////////////
PidVector ProcessEnumerator::getMatchingPids(LPCTSTR process)
{
	PidVector output;

	for (int i = 0; i < pids.size(); i++) {
		tstring name = getProcessName(pids[i]);

		tstring basename = getBaseName(name.c_str());
		tstring baseproc = getBaseName(process);

		if (_tcsnicmp(basename.c_str(), baseproc.c_str(), 
			baseproc.length()) == 0)
			output.push_back(pids[i]);
	}

	return output;
}

/////////////////////////////////////////////////////////////////////////////
tstring ProcessEnumerator::getProcessName(DWORD pid) const
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 
		FALSE, pid);
	if (hProcess == NULL)
		return _T("");

	HMODULE hModule;
	DWORD needed;

	if (!(*EnumProcessModules)(hProcess, &hModule, sizeof(hModule), &needed)) {
		CloseHandle(hProcess);
		return _T("");
	}

	TCHAR module[_MAX_PATH + _MAX_FNAME + 1];
	module[0] = _T('\0');
	
	DWORD rtn = (*GetModuleFileNameEx)(hProcess, hModule, module, 
		_MAX_PATH + _MAX_FNAME);
	
	CloseHandle(hProcess);
	
	return module;
}

/////////////////////////////////////////////////////////////////////////////
tstring ProcessEnumerator::getBaseName(LPCTSTR process)
{	
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];

	_tsplitpath(process, drive, dir, fname, ext );
    
	return fname;
}

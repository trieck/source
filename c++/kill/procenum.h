/////////////////////////////////////////////////////////////////////////////
//
//	PROCENUM.H : NT process enumerator
//

#ifndef __PROCENUM_H__
#define __PROCENUM_H__

typedef vector<DWORD> PidVector;

/////////////////////////////////////////////////////////////////////////////
class ProcessEnumerator {
// Construction / Destruction
public:
    ProcessEnumerator();
    virtual ~ProcessEnumerator();

// Interface
    tstring getProcessName(DWORD pid) const;
    PidVector getMatchingPids(LPCTSTR process);
// Implementation
protected:
    void enumerate();
    tstring getBaseName(LPCTSTR process);
private:
    typedef BOOL (WINAPI *EnumProcessesProc)(DWORD *ids, DWORD size,
            DWORD *needed);
    typedef DWORD (WINAPI *GetModuleBaseNameProc)(HANDLE hProcess,
            HMODULE hModule, LPTSTR lpFilename, DWORD nSize);
    typedef DWORD (WINAPI *GetModuleFileNameExProc)(HANDLE hProcess,
            HMODULE hModule, LPTSTR lpFilename, DWORD nSize);
    typedef BOOL (WINAPI *EnumProcessModulesProc)(HANDLE hProcess,
            HMODULE *hMods, DWORD size, DWORD *needed);

    HMODULE hModule;
    PidVector pids;
    enum { maxpids = 1000 };
    EnumProcessesProc EnumProcesses;
    EnumProcessModulesProc EnumProcessModules;
    GetModuleBaseNameProc GetModuleBaseName;
    GetModuleFileNameExProc GetModuleFileNameEx;
};
/////////////////////////////////////////////////////////////////////////////

#endif __PROCENUM_H__
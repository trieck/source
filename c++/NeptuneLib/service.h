/////////////////////////////////////////////////////////////////////////////
//
//	SERVICE.H : NT Service class
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __SERVICE_H__
#define __SERVICE_H__

/////////////////////////////////////////////////////////////////////////////
class Service
{
// Construction
public:
    Service(LPCTSTR name);
    virtual ~Service();

// Interface
    BOOL Execute(int argc, TCHAR** argv);
    DWORD GetExitCode() const;

// Implementation
protected:
    static void WINAPI ServiceMain(DWORD argc, TCHAR** argv);
    static void WINAPI Handler(DWORD opcode);
    void ConsoleMain(DWORD argc, TCHAR** argv);
    BOOL SetStatus(DWORD state);
    BOOL InstallService() const;
    BOOL UninstallService() const;
    BOOL IsInstalled() const;

    virtual BOOL OnInit();
    virtual void OnStop();
    virtual void OnPause();
    virtual void OnInterrogate();
    virtual void OnShutdown();
    virtual void OnContinue();
    virtual void Run();
private:
    tstring m_name;
    SERVICE_STATUS m_Status;
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    DWORD m_ServiceThreadID;
    static Service *m_pThis;
};
/////////////////////////////////////////////////////////////////////////////

inline DWORD Service::GetExitCode() const
{
    return m_Status.dwWin32ExitCode;
}

#endif // __SERVICE_H__

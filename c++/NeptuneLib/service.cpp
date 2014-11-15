/////////////////////////////////////////////////////////////////////////////
//
//	SERVICE.CPP : NT service class
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "service.h"
#include "elog.h"

Service* Service::m_pThis = NULL;
static LPCTSTR usage = _T("usage: <service> -i -u");

/////////////////////////////////////////////////////////////////////////////
Service::Service(LPCTSTR name)
    : m_name(name)
{
    m_pThis = this;
    m_ServiceThreadID = 0UL;
    m_hServiceStatus = NULL;
    m_Status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_Status.dwCurrentState = SERVICE_STOPPED;
    m_Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_Status.dwWin32ExitCode = 0UL;
    m_Status.dwServiceSpecificExitCode = 0UL;
    m_Status.dwCheckPoint = 0UL;
    m_Status.dwWaitHint = 0UL;
}

/////////////////////////////////////////////////////////////////////////////
Service::~Service()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::Execute(int argc, TCHAR **argv)
{
    // Check for installation options
    if (argc > 1) {
        if (_tcscmp(argv[1], _T("-i")) == 0) {
            if (IsInstalled())
                cerr << "service is already installed." << endl;
            else if (InstallService())
                cout << "service installed successfully." << endl;
            else cerr << "unable to install service." << endl;
        }
        else if (_tcscmp(argv[1], _T("-u")) == 0) {
            if (!IsInstalled())
                cerr << "service is not installed." << endl;
            else if (UninstallService())
                cout << "service uninstalled successfully." << endl;
            else cerr << "unable to uninstall service." << endl;
        }
        else cerr << usage << endl;

        return FALSE;
    }

    SERVICE_TABLE_ENTRY st[] = {
        (LPTSTR)m_name.c_str(), ServiceMain,
        NULL, NULL
    };

    if (!StartServiceCtrlDispatcher(st)) {
        // Check to see if we are running as a console
        if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) {
            ConsoleMain(argc, argv);
            return TRUE;
        }
        return FALSE;
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void Service::ServiceMain(DWORD argc, TCHAR** argv)
{
    m_pThis->m_ServiceThreadID = GetCurrentThreadId();
    m_pThis->m_hServiceStatus = RegisterServiceCtrlHandler(
        m_pThis->m_name.c_str(), Handler);

    m_pThis->m_Status.dwWin32ExitCode = 0;
    m_pThis->m_Status.dwCheckPoint = 0;
    m_pThis->m_Status.dwWaitHint = 0;

    m_pThis->SetStatus(SERVICE_START_PENDING);

    if (m_pThis->OnInit()) {
        m_pThis->SetStatus(SERVICE_RUNNING);
        m_pThis->Run();
    }

    m_pThis->SetStatus(SERVICE_STOPPED);
}

/////////////////////////////////////////////////////////////////////////////
void Service::ConsoleMain(DWORD argc, TCHAR** argv)
{
    m_pThis->m_ServiceThreadID = GetCurrentThreadId();
    m_pThis->m_hServiceStatus = NULL;
    m_pThis->m_Status.dwWin32ExitCode = 0;
    m_pThis->m_Status.dwCheckPoint = 0;
    m_pThis->m_Status.dwWaitHint = 0;

    if (m_pThis->OnInit()) {
        m_pThis->Run();
    }
}

/////////////////////////////////////////////////////////////////////////////
void Service::Handler(DWORD opcode)
{
    switch (opcode) {
    case SERVICE_CONTROL_STOP:			// 1
    case SERVICE_CONTROL_PAUSE:			// 2
    case SERVICE_CONTROL_CONTINUE:		// 3
    case SERVICE_CONTROL_INTERROGATE:	// 4
    case SERVICE_CONTROL_SHUTDOWN:		// 5
        ::PostThreadMessage(m_pThis->m_ServiceThreadID, WM_USER, opcode, 0);
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
void Service::Run()
{
    // We use a message loop here because this is arguably the easiest
    // way to deal with the potential race conditions that exist between
    // the service thread and the handler thread.  The SCM will make no
    // provisions for synchronizing status activity, the best bet is to
    // ensure that all calls are handled through the service main thread.
    MSG msg;
    while (GetMessage(&msg, NULL, WM_USER, WM_USER) > 0) {
        WPARAM opcode = msg.wParam;
        if (opcode == SERVICE_CONTROL_STOP) {
            SetStatus(SERVICE_STOP_PENDING);
            OnStop();
            break;
        }
        else if (opcode == SERVICE_CONTROL_PAUSE) {
            OnPause();
        }
        else if (opcode == SERVICE_CONTROL_CONTINUE) {
            OnContinue();
        }
        else if (opcode == SERVICE_CONTROL_INTERROGATE) {
            OnInterrogate();
        }
        else if (opcode == SERVICE_CONTROL_SHUTDOWN) {
            OnShutdown();
        }
        ::SetServiceStatus(m_pThis->m_hServiceStatus, &m_pThis->m_Status);
    }
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::SetStatus(DWORD state)
{
    m_Status.dwCurrentState = state;

    return ::SetServiceStatus(m_hServiceStatus, &m_Status);
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::OnInit()
{
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void Service::OnStop()
{
}

/////////////////////////////////////////////////////////////////////////////
void Service::OnPause()
{
}

/////////////////////////////////////////////////////////////////////////////
void Service::OnInterrogate()
{
}

/////////////////////////////////////////////////////////////////////////////
void Service::OnContinue()
{
}

/////////////////////////////////////////////////////////////////////////////
void Service::OnShutdown()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::InstallService() const
{
    // Open the Service Control Manager
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
        return FALSE;

    // Get the executable file path
    TCHAR path[_MAX_PATH + _MAX_FNAME + 1];
    ::GetModuleFileName(NULL, path, sizeof(path));

    // Create the service
    SC_HANDLE hService = ::CreateService(hSCM,
        m_name.c_str(),
        m_name.c_str(),
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,        // start condition
        SERVICE_ERROR_NORMAL,
        path,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);
    if (hService == NULL) {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

    EventLog::loginfo(_T("The service was installed"));

    // tidy up
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::UninstallService() const
{
    // Open the Service Control Manager
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
        return FALSE;

    BOOL bResult = FALSE;
    SC_HANDLE hService = ::OpenService(hSCM,
        m_name.c_str(),
        DELETE);

    if (hService != NULL) {
        if (::DeleteService(hService)) {
            EventLog::loginfo(_T("The service was removed"));
            bResult = TRUE;
        }
        else {
            EventLog::logerr(_T("The service could not be removed"));
        }
        ::CloseServiceHandle(hService);
    }

    ::CloseServiceHandle(hSCM);

    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
BOOL Service::IsInstalled() const
{
    BOOL bResult = FALSE;

    // Open the Service Control Manager
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM != NULL) {
        // Try to open the service
        SC_HANDLE hService = ::OpenService(hSCM, m_name.c_str(),
            SERVICE_QUERY_CONFIG);
        if (hService != NULL) {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }

        ::CloseServiceHandle(hSCM);
    }

    return bResult;
}

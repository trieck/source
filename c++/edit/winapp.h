/////////////////////////////////////////////////////////////////////////////
//
// WINAPP.H : application class
//
// Copyright (c) 1999 Rieck Enterprises
//

#ifndef __WINAPP_H__
#define __WINAPP_H__

/////////////////////////////////////////////////////////////////////////////
class WinApp {
    friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                              LPSTR command, int nCmdShow);

// Construction / Destruction
protected:
    WinApp();
public:
    virtual ~WinApp();

// Interface
    HINSTANCE GetCurrentInstance() const;
    int GetShow() const;

// Implementation
protected:
    virtual BOOL InitInstance() = 0;
    virtual int Run();
    virtual int ExitInstance();
private:
    HINSTANCE m_hInstance;
    string m_command;
    int m_nCmdShow;
    int m_nExitCode;			// exit code returned to WinMain
};
/////////////////////////////////////////////////////////////////////////////

inline HINSTANCE WinApp::GetCurrentInstance() const
{
    return m_hInstance;
}

inline int WinApp::GetShow() const
{
    return m_nCmdShow;
}

extern WinApp * pApp;

#endif // __WINAPP_H__



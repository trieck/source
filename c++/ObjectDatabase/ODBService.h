/////////////////////////////////////////////////////////////////////////////
//
// ODBSERVICE.H : Object Database Service
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ODBSERVICE_H__
#define __ODBSERVICE_H__

/////////////////////////////////////////////////////////////////////////////
class ODBService : public Service, IRunnable
{
public:
    // Construction / Destruction
    ODBService();
    ~ODBService();

// Interface
    virtual LPCSTR GetServiceName() const;

// Implementation
private:
    DWORD Execute(LPVOID pdata);
    virtual BOOL OnInit();
    virtual void Run();
    virtual void OnStop();

    enum { LISTEN_PORT = 5001 };

    Connection conn;
    CThreadPool<::Handler> pool;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline LPCSTR ODBService::GetServiceName() const
{
    return "Object Database Service";
}

#endif // __ODBSERVICE_H__
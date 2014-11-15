/////////////////////////////////////////////////////////////////////////////
//
// ODBSERVICE.CPP : Object Database Service
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "wthread.h"
#include <atlutil.h>
#include "Service.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "Handler.h"
#include "ODBService.h"
#include "ELog.h"

/////////////////////////////////////////////////////////////////////////////
ODBService::ODBService()
{
}

/////////////////////////////////////////////////////////////////////////////
ODBService::~ODBService()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL ODBService::OnInit()
{
    if (S_OK != pool.Initialize())
        return FALSE;

    if (!conn.listen(LISTEN_PORT, SOMAXCONN)) {
        EventLog::logerr("ODBService::Init() listen error : %s",
                         lasterror().c_str());
        return FALSE;
    }

    return TRUE;
}

void ODBService::Run()
{
    // Perform actual work in a separate thread
    WorkerThread worker(this);
    worker.Start();

    // Call the base class implementation
    Service::Run();
}

void ODBService::OnStop()
{
    pool.Shutdown();
    Service::OnStop();
}

/////////////////////////////////////////////////////////////////////////////
DWORD ODBService::Execute(LPVOID pdata)
{
    for (;;) {
        Connection remote = conn.accept();
        if (!remote.valid())
            continue;

        remote.release();	// ownership in another thread
        pool.QueueRequest(&remote);
    }

    return 0;
}

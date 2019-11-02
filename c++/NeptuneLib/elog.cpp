/////////////////////////////////////////////////////////////////////////////
//
//	ELOG.CPP : NT event logging interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "elog.h"
#include "messages.h"
#include "util.h"

#define MAXMSG 4096

static BOOL log(LPCTSTR message, WORD type);

namespace EventLog
{

/////////////////////////////////////////////////////////////////////////////
void logerr(LPCTSTR format, ...)
{
    va_list arglist;
    va_start(arglist, format);

    TCHAR msg[MAXMSG];
    _vstprintf(msg, format, arglist);

    va_end (arglist);

    log(msg, EVENTLOG_ERROR_TYPE);
}

/////////////////////////////////////////////////////////////////////////////
void logwarn(LPCTSTR format, ...)
{
    va_list arglist;
    va_start(arglist, format);

    TCHAR msg[MAXMSG];
    _vstprintf(msg, format, arglist);

    va_end (arglist);

    log(msg, EVENTLOG_WARNING_TYPE);
}

/////////////////////////////////////////////////////////////////////////////
void loginfo(LPCTSTR format, ...)
{
    va_list arglist;
    va_start(arglist, format);

    TCHAR msg[MAXMSG];
    _vstprintf(msg, format, arglist);

    va_end (arglist);

    log(msg, EVENTLOG_INFORMATION_TYPE);
}

}	// namespace

/////////////////////////////////////////////////////////////////////////////
BOOL log(LPCTSTR message, WORD type)
{
    tstring machine = machinename();
    tstring module = modulename();
    tstring source = filename(module.c_str());

    // Register the event source
    HANDLE hEventLog = RegisterEventSource(machine.c_str(), source.c_str());
    if (hEventLog == NULL)
        return FALSE;

    // Report the event
    BOOL f = ::ReportEvent(hEventLog, type, CAT_ELOG, EVMSG_GENERIC,
                           NULL, 1, 0, &message, NULL);

    // Deregister the event source
    DeregisterEventSource(hEventLog);

    return f;
}

/////////////////////////////////////////////////////////////////////////////
//
//	ELOG.H : NT event logging interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ELOG_H__
#define __ELOG_H__

namespace EventLog
{
void logerr(LPCTSTR format, ...);
void logwarn(LPCTSTR format, ...);
void loginfo(LPCTSTR format, ...);
};

#endif // __ELOG_H__
/////////////////////////////////////////////////////////////////////////////
//
//	ELOG.H : NT event logging interface
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __ELOG_H__
#define __ELOG_H__

namespace EventLog {
void logerr(const char *format, ...);
void logwarn(const char *format, ...);
void loginfo(const char *format, ...);
};

#endif // __ELOG_H__
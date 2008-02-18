/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.CPP : simple exception class
//
//	Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved.
//

#include "common.h"
#include "exception.h"
#include <stdarg.h>

/////////////////////////////////////////////////////////////////////////////
Exception::Exception(const char *fmt, ...)
{
	va_list arglist;
    va_start(arglist, fmt);

    char buff[1000];
    _vsnprintf(buff, 1000, fmt, arglist);

    va_end (arglist);

	description = buff;
}

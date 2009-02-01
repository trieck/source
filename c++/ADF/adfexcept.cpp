/////////////////////////////////////////////////////////////////////////////
//
// ADFEXCEPT.CPP : simple exception class
//
// Copyright(c) 2009 Thomas A. Rieck, All Rights Reserved
//

#include "common.h"
#include "adfexcept.h"
#include <stdarg.h>

/////////////////////////////////////////////////////////////////////////////
ADFException::ADFException()
{
	description = strerror(errno);
}

/////////////////////////////////////////////////////////////////////////////
ADFException::ADFException(const char *fmt, ...)
{
	va_list arglist;
    char buff[256];

	va_start(arglist, fmt);
	vsnprintf(buff, 256, fmt, arglist);
    va_end (arglist);

	description = buff;
}
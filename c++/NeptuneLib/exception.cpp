/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.CPP : simple exception class
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "exception.h"

namespace {
const int BUFFSIZE = 4096;
}

/////////////////////////////////////////////////////////////////////////////
Exception::Exception(const char *fmt, ...)
{
	va_list arglist;
	va_start(arglist, fmt);

	char buff[BUFFSIZE];
	vsprintf(buff, fmt, arglist);

	va_end (arglist);

	description = buff;
}

/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.CPP : simple exception class
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "PlutoLib.h"
#include "exception.h"

/////////////////////////////////////////////////////////////////////////////
Exception::Exception(const TCHAR *fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);

    TCHAR buff[1000];
    _vsntprintf(buff, 1000, fmt, arglist);

    va_end (arglist);

    m_description = buff;
}

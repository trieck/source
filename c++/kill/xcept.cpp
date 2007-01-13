/////////////////////////////////////////////////////////////////////////////
// 
//	XCEPT.CPP : simple text exception
//

#include "common.h"
#include "xcept.h"

#define MAX_BUFFER 4096

/////////////////////////////////////////////////////////////////////////////
Exception::Exception(LPTSTR fmt, ...)
{
	TCHAR buffer[MAX_BUFFER];

	va_list list;
    va_start(list, fmt);
    int count = _vstprintf(buffer, fmt, list);
	va_end(list);
	_text = buffer;
}

/////////////////////////////////////////////////////////////////////////////
Exception::~Exception()
{
}


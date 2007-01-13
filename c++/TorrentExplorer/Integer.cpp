// Integer.cpp: implementation of the Integer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Integer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Integer::Integer(__int64 val) : value(val)
{
}

Integer::Integer(const Integer &rhs)
{
	*this = rhs;
}

Integer::~Integer()
{
}

Integer &Integer::operator =(const Integer &rhs)
{
	if (this != &rhs) {
		value = rhs.value;
	}

	return *this;
}



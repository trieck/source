// Integer.h: interface for the Integer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTEGER_H__729C50EE_2AD0_4124_986C_607F6E6CFAB6__INCLUDED_)
#define AFX_INTEGER_H__729C50EE_2AD0_4124_986C_607F6E6CFAB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TorrentObject.h"

class Integer : public TorrentObject  
{
public:
	Integer(__int64 val);
	Integer(const Integer &rhs);

	virtual ~Integer();

	Integer &operator =(const Integer &rhs);
	virtual int GetElementType() const { return ET_INTEGER; }
	operator __int64() const { return value; }

private:
	__int64 value;
};

typedef Integer *LPINTEGER;

#endif // !defined(AFX_INTEGER_H__729C50EE_2AD0_4124_986C_607F6E6CFAB6__INCLUDED_)

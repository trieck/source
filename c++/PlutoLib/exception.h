/////////////////////////////////////////////////////////////////////////////
//
//	EXCEPTION.H : simple exception class
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __EXCEPTION_INCLUDE_H__
#define __EXCEPTION_INCLUDE_H__

/////////////////////////////////////////////////////////////////////////////
class Exception
{
public:
	Exception(const tstring &msg) { m_description = msg; }
	Exception(const Exception & E) { *this = E; }
	Exception(const TCHAR *fmt, ...);
	Exception & operator = (const Exception & E) {
		if (this != & E)
			m_description = E.m_description;
		return *this;
	}
	tstring GetDescription() const { return m_description; }
private:
	tstring m_description;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __EXCEPTION_INCLUDE_H__
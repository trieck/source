/////////////////////////////////////////////////////////////////////////////
//
// NETERROR.H : network error class
//
// Copyright(c) 2000 Thomas A. Rieck
//

#ifndef __NETERROR_H__
#define __NETERROR_H__

/////////////////////////////////////////////////////////////////////////////
class NetError
{
// Construction / Destruction
public:
	NetError();
	NetError(const NetError &);
	virtual ~NetError();

// Interface
	NetError & operator = (const NetError & E);
	DWORD GetErrorCode() const { return m_errorcode; };
	CString GetDescription() const { return (LPCTSTR)m_description; }
	CString GetProvider() const { return (LPCTSTR)m_provider; }

protected:
// Implementation
	void create();

private:
	DWORD m_errorcode;
	CString m_description;
	CString m_provider;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __NETERROR_H__
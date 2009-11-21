/////////////////////////////////////////////////////////////////////////////
//
// NETENUM.H : network resource enumerator class
//
// Copyright(c) 2000 Thomas A. Rieck
//

#ifndef __NETENUM_H__
#define __NETENUM_H__

#include <memory>
#include "neterror.h"

// forward declarations
class NetResourceEnum;

typedef std::auto_ptr<NetResourceEnum> LPNETRESOURCEENUM;

/////////////////////////////////////////////////////////////////////////////
class NetResourceEnum : public NETRESOURCE {
// Construction / Destruction
protected:
	NetResourceEnum(LPNETRESOURCE);
	NetResourceEnum(HANDLE);
public:
	virtual ~NetResourceEnum();

// Interface
	DWORD count() const;
	LPNETRESOURCEENUM GetAt(DWORD index);

protected:
// Implementation
	void InitializeRes();
	void FillBuffers();

private:
	HANDLE m_hEnum;			// enumeration handle
	LPNETRESOURCE m_pres;	// array of network resources
	DWORD m_buffers;		// number of entires in m_pres

	friend LPNETRESOURCEENUM GetRootEnum();
};
/////////////////////////////////////////////////////////////////////////////

inline DWORD NetResourceEnum::count() const
{
	return m_buffers;
}

// global helpers
LPNETRESOURCEENUM GetRootEnum();

#endif // __NETENUM_H__
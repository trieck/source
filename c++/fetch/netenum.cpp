/////////////////////////////////////////////////////////////////////////////
//
// NETENUM.CPP : network resource enumerator class
//
// Copyright(c) 2000 Thomas A. Rieck
//

#include "stdafx.h"
#include "netenum.h"

#define ALLENTRIES 0xFFFFFFFF
#define BUFFSIZE 0x4000

// Helper functions
static HANDLE OpenResource(LPNETRESOURCE res);

NetResourceEnum::NetResourceEnum(LPNETRESOURCE res)
{
	ASSERT(res != NULL);
	m_hEnum = NULL;
	m_pres = NULL;
	m_buffers = 0UL;
	
	memcpy((LPNETRESOURCE)this, res, sizeof(NETRESOURCE));
	
	// is this a container resource
	if ((res->dwUsage & RESOURCEUSAGE_CONTAINER) != 0) {
		m_hEnum = OpenResource(res);
		if (m_hEnum == NULL)
			throw NetError();	
		FillBuffers();
	}
}

// root ctor
NetResourceEnum::NetResourceEnum(HANDLE hEnum)
{
	ASSERT(hEnum != NULL);
	m_hEnum = hEnum;
	InitializeRes();
	FillBuffers();
	ASSERT(m_pres != NULL);
}

NetResourceEnum::~NetResourceEnum()
{
	if (m_hEnum != NULL) {
		::WNetCloseEnum(m_hEnum);
		m_hEnum = NULL;
	}
	if (m_pres != NULL) {
		::GlobalFree(m_pres);
		m_pres = NULL;
	}
	m_buffers = 0UL;
}

void NetResourceEnum::InitializeRes()
{
	dwScope = 0UL;
    dwType = 0UL;
    dwDisplayType = 0UL;
    dwUsage = 0UL;
    lpLocalName = NULL;
    lpRemoteName = NULL;
    lpComment = NULL;
    lpProvider = NULL;
}

void NetResourceEnum::FillBuffers()
{
	m_buffers = ALLENTRIES;
	DWORD buffersize = BUFFSIZE;
	DWORD rtn;

	ASSERT(m_hEnum != NULL);
	m_pres = NULL;

	for (;;) {
		m_buffers = ALLENTRIES;
		
		if (m_pres) GlobalFree(m_pres);
		m_pres = (LPNETRESOURCE)GlobalAlloc(GPTR, buffersize);
		if (m_pres == NULL)	{ // allocation error 
			m_buffers = 0UL;
			break;
		}
		
		rtn = ::WNetEnumResource(
			m_hEnum,		// handle to enumeration
			&m_buffers,		// pointer to entries to list
			m_pres,			// pointer to buffer for results
			&buffersize		// pointer to buffer size variable
		);

  		if (rtn == NO_ERROR || rtn == ERROR_NO_MORE_ITEMS)
			break;
	}
}

LPNETRESOURCEENUM NetResourceEnum::GetAt(DWORD index)
{
	ASSERT(m_pres != NULL);

	if (index > m_buffers - 1)
		return NULL; // out of range

	return new NetResourceEnum(&m_pres[index]);
}

// Helper functions
LPNETRESOURCEENUM GetRootEnum()
{
	return new NetResourceEnum(OpenResource(NULL));
}

HANDLE OpenResource(LPNETRESOURCE res)
{
	// only supports disk types

	HANDLE hEnum = NULL;

	DWORD rtn = ::WNetOpenEnum(
		RESOURCE_GLOBALNET,	// scope of enumeration
		RESOURCETYPE_DISK,	// resource types to list
		0,					// resource usage to list
		res,				// pointer to resource structure
		&hEnum				// pointer to enumeration handle buffer
		);
 	
	return hEnum;
}



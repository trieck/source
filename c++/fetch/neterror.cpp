/////////////////////////////////////////////////////////////////////////////
//
// NETERROR.CPP : network error class
//
// Copyright(c) 2000 Thomas A. Rieck
//

#include "stdafx.h"
#include "neterror.h"

NetError::NetError()
{
	create();
}

NetError::~NetError()
{
}

NetError::NetError(const NetError & E)
{
	m_errorcode = E.m_errorcode;
	m_description = E.m_description;
	m_provider = E.m_provider;
}

NetError & NetError::operator = (const NetError & E)
{
	if (this != & E) {
		m_errorcode = E.m_errorcode;
		m_description = E.m_description;
		m_provider = E.m_provider;
	}

	return *this;
}

void NetError::create()
{
	TCHAR provider[256] = "";
	TCHAR description[256] = "";
	
	WNetGetLastError(&m_errorcode,
		description, 
		256,
		provider,
		256);

	m_description = description;
	m_provider = provider;
}



/////////////////////////////////////////////////////////////////////////////
//
// DATABASE.CPP : Encapsulates an ADO database connection
//
// Copyright(c) 2008 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "database.h"

/////////////////////////////////////////////////////////////////////////////
Database::Database()
{
}

/////////////////////////////////////////////////////////////////////////////
Database::~Database()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
void Database::open(LPCTSTR uid, LPCTSTR pwd, LPCTSTR connStr) throw()
{
	close();

	m_Conn.CreateInstance(__uuidof(ADODB::Connection));
	m_Conn->Open(connStr, uid, pwd, NULL);
}

/////////////////////////////////////////////////////////////////////////////
void Database::open(LPCTSTR provider, LPCTSTR path) throw()
{
	close();

	m_Conn.CreateInstance(__uuidof(ADODB::Connection));
	m_Conn->PutProvider(provider);
	m_Conn->Open(path, (BSTR)NULL, (BSTR)NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
RecPtr Database::execute(LPCTSTR command) throw()
{
	RecPtr results;

	if (m_Conn == NULL)
		return results;

	return m_Conn->Execute(command, NULL, 0);
}

/////////////////////////////////////////////////////////////////////////////
void Database::close() throw()
{
	if (m_Conn != NULL) {
		m_Conn->raw_Close();	// might not be open
		m_Conn.Release();
	}
}

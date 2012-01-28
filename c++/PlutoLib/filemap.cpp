/////////////////////////////////////////////////////////////////////////////
//
//	FILEMAP.CPP : Windows file mapping interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "PlutoLib.h"
#include "filemap.h"

/////////////////////////////////////////////////////////////////////////////
FileMapping::FileMapping()
: m_hMapping(NULL), m_hFile(NULL), m_pView(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
FileMapping::~FileMapping()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
void FileMapping::Close() 
{
    UnmapView();

	if (m_hMapping != NULL) {
		CloseHandle(m_hMapping);
		m_hMapping = NULL;
	}

    if (m_hFile != NULL) {
        CloseHandle(m_hFile);
        m_hFile = NULL;
    }
}

/////////////////////////////////////////////////////////////////////////////
bool FileMapping::Create(LPCTSTR lpszFilename, DWORD dwDesiredAccess,
    DWORD dwShareMode, DWORD dwCreationDisposition, 
    DWORD dwFlagsAndAttributes, DWORD dwProtect)
{
	Close();

    if ((m_hFile = CreateFile(lpszFilename, dwDesiredAccess, dwShareMode, 
        NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL)) 
        == INVALID_HANDLE_VALUE)
        return false;

	m_hMapping = CreateFileMapping(m_hFile, NULL, dwProtect, 0, 0, NULL);
	
	return m_hMapping != NULL;
}

/////////////////////////////////////////////////////////////////////////////
LPVOID FileMapping::MapView(DWORD access, uint64_t offset, uint32_t nbytes)
{
    UnmapView();

	ULARGE_INTEGER li; li.QuadPart = offset;
	m_pView = MapViewOfFile(m_hMapping, access, li.HighPart, li.LowPart, 
        nbytes);
    return m_pView;
}

/////////////////////////////////////////////////////////////////////////////
bool FileMapping::UnmapView()
{
    bool bResult = false;

    if (m_pView != NULL) {
        bResult = (UnmapViewOfFile(m_pView) == TRUE);
        m_pView = NULL;
    }

    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
bool FileMapping::FlushView(uint32_t nbytes)
{
    bool bResult = false;

    if (m_pView != NULL) {
	    bResult = (FlushViewOfFile(m_pView, nbytes) == TRUE);
    }

    return bResult;
}

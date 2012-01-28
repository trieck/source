/////////////////////////////////////////////////////////////////////////////
//
// FILESTREAM.CPP : Buffered sequential file stream class
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "PlutoLib.h"
#include "filestream.h"

/////////////////////////////////////////////////////////////////////////////
FileStream::FileStream() 
 : m_hFile(INVALID_HANDLE_VALUE), m_cRef(0), m_nbuf(0), m_Flags(0)
 , m_BlockSize(0), m_Access(0),	m_ShareMode(0), m_Disposition(0)
{
	Alloc(); 
    AddRef();	// not externally creatable
}

/////////////////////////////////////////////////////////////////////////////
FileStream::~FileStream()
{
	Close();
	Free();
}

/////////////////////////////////////////////////////////////////////////////
ULONG FileStream::AddRef(void)
{
    return ++m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
ULONG FileStream::Release(void)
{
	if (--m_cRef == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::QueryInterface(REFIID riid, void** ppv)
{
    *ppv = NULL;

    if (riid == IID_IUnknown)
        *ppv = this;
    if (riid == IID_ISequentialStream)
        *ppv = this;
    
    if(*ppv) {
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Read(void *pv, ULONG cb, ULONG* pcbRead)
{
    if (pcbRead)
        *pcbRead = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

	uint8_t* p = (uint8_t*)pv;
	uint32_t k, n = cb;

	while (n) {
		if (m_nbuf == 0) {	// buffer empty
			if (!ReadBlock())
				return HRESULT_FROM_WIN32(GetLastError());
		}
		
		if (m_nbuf == 0) {	// EOF
			*pcbRead = cb - n;
			return S_OK;
		}

		k = min(n, m_nbuf);
		memcpy(p, m_pbuf, k);
		n -= k;
		p += k;
		m_pbuf += k;
		m_nbuf -= k;
	}

	*pcbRead = cb;

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
BOOL FileStream::ReadBlock()
{
	ULONG read;
	if (!ReadFile(m_hFile, m_buf, m_BlockSize, &read, NULL))
		return FALSE;

	m_pbuf = m_buf;
	m_nbuf = read;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL FileStream::WriteBlock()
{
	ULONG written;

	// if using non-buffered i/o, buffer size must be a multiple
	// of the sector size.  In the case of writing a partial block, we must
	// align the buffer size to a multiple of the sector size.
	if (m_Flags & FILE_FLAG_NO_BUFFERING) {	
		if (DWORD(m_pbuf - m_buf) < m_BlockSize) {	// incomplete block
			DWORD dwSize = SectorAlign(m_pbuf - m_buf);
			DWORD dwBump = dwSize - (m_pbuf - m_buf);
			m_pbuf += dwBump;
		}
	}

	if (!WriteFile(m_hFile, m_buf, m_pbuf - m_buf, &written, NULL))
		return FALSE;

	m_pbuf = m_buf;
	m_nbuf = m_BlockSize;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Write(const void *pv, ULONG cb, ULONG* pcbWritten)
{
	if (pcbWritten)
		*pcbWritten = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

	uint8_t* p = (uint8_t*)pv;
	uint32_t k, n = cb;

	while (n) {
		if (m_nbuf == 0) {	// buffer full
			if (!WriteBlock())
				return HRESULT_FROM_WIN32(GetLastError());
		}
		
		k = min(n, m_nbuf);
		memcpy(m_pbuf, p, k);
		n -= k;
		p += k;
		m_pbuf += k;
		m_nbuf -= k;
	}

	*pcbWritten = cb;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
void FileStream::Alloc()
{
	m_BlockSize = SectorSize() * 128;
	m_pbuf = m_buf = (uint8_t*)CoTaskMemAlloc(m_BlockSize);
	memset(m_buf, 0, m_BlockSize);
}

/////////////////////////////////////////////////////////////////////////////
void FileStream::Free()
{
	CoTaskMemFree(m_buf);
}

/////////////////////////////////////////////////////////////////////////////
FileStream *FileStream::Create(LPCTSTR lpFileName, DWORD dwDesiredAccess, 
	DWORD dwShareMode, DWORD dwCreationDisposition, 
	DWORD dwFlagsAndAttributes) 
{
	FileStream *pStream = new FileStream();
	if (!pStream->Open(lpFileName, dwDesiredAccess, dwShareMode, 
		dwCreationDisposition, dwFlagsAndAttributes)) {
			pStream->Release();
			return NULL;		
	}

	return pStream;
}

/////////////////////////////////////////////////////////////////////////////
BOOL FileStream::Open(LPCTSTR lpFileName, DWORD dwDesiredAccess,
 DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
{
	Close();

	m_FileName = lpFileName;
	m_Access = dwDesiredAccess;
	m_ShareMode = dwShareMode;
	m_Disposition = dwCreationDisposition;
	m_Flags = dwFlagsAndAttributes | FILE_FLAG_SEQUENTIAL_SCAN;

	m_hFile = CreateFile(lpFileName, dwDesiredAccess, dwShareMode, NULL,
		dwCreationDisposition, m_Flags, NULL);
	return m_hFile != INVALID_HANDLE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Close() 
{
	if (m_hFile != INVALID_HANDLE_VALUE) {
		// flush file buffers
		if ((m_Access & GENERIC_WRITE) && m_pbuf > m_buf) {
			DWORD toWrite = m_pbuf - m_buf;
			if (!WriteBlock())
				return HRESULT_FROM_WIN32(GetLastError());

			// if using non-buffered i/o, we must truncate the file
			// if the last block written was not a multiple of the 
			// sector size.
			if (m_Flags & FILE_FLAG_NO_BUFFERING) {
				DWORD dwSize = SectorAlign(toWrite);
				DWORD bump = dwSize - toWrite;
				
				// close and reopen the file using buffered i/o
				CloseHandle(m_hFile);
				m_Flags &= ~FILE_FLAG_NO_BUFFERING;

				m_hFile = CreateFile(m_FileName.c_str(), m_Access, m_ShareMode, 
					NULL, OPEN_EXISTING, m_Flags, NULL);
				if (m_hFile == INVALID_HANDLE_VALUE)
					return HRESULT_FROM_WIN32(GetLastError());

				// calculate new size
				LARGE_INTEGER size;
				HRESULT hr = GetFileSize(&size);
				if (FAILED(hr))
					return HRESULT_FROM_WIN32(GetLastError());

				size.QuadPart -= bump;

				DWORD dwPtrLow = SetFilePointer(m_hFile, size.LowPart, 
					&size.HighPart, FILE_BEGIN);
				if (dwPtrLow == INVALID_SET_FILE_POINTER && 
					(GetLastError() != NO_ERROR)) {
					return HRESULT_FROM_WIN32(GetLastError());
				}

				if (!SetEndOfFile(m_hFile))
					return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::GetFileSize(PLARGE_INTEGER pFileSize)
{
	pFileSize->LowPart = ::GetFileSize(m_hFile, (LPDWORD)&pFileSize->HighPart);
	if (pFileSize->LowPart == INVALID_FILE_SIZE && 
		(GetLastError() != NO_ERROR)) {
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
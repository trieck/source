/////////////////////////////////////////////////////////////////////////////
//
//	FILESTREAM.CPP : file based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "FileStream.h"

/////////////////////////////////////////////////////////////////////////////
FileStream::FileStream()
    : hFile(INVALID_HANDLE_VALUE), m_cRef(0)
{
    // The constructor AddRef's
    AddRef();
}

/////////////////////////////////////////////////////////////////////////////
FileStream::~FileStream()
{
    Close();
}

/////////////////////////////////////////////////////////////////////////////
FileStream * FileStream::Create(LPCSTR lpFileName, DWORD dwDesiredAccess,
                                DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
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
BOOL FileStream::Open(LPCSTR lpFileName, DWORD dwDesiredAccess,
                      DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
{
    Close();
    hFile = CreateFile(lpFileName, dwDesiredAccess, dwShareMode, NULL,
                       dwCreationDisposition, dwFlagsAndAttributes, NULL);
    return hFile != INVALID_HANDLE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////
void FileStream::Close()
{
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}

/////////////////////////////////////////////////////////////////////////////
ULONG FileStream::AddRef()
{
    return ++m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
ULONG FileStream::Release()
{
    if (--m_cRef == 0) {
        delete this;
        return 0;
    }

    return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::QueryInterface(REFIID riid, LPVOID *ppv)
{
    *ppv = NULL;

    if (riid == IID_IUnknown)
        *ppv = this;
    if (riid == IID_ISequentialStream)
        *ppv = this;

    if (*ppv) {
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
    *pcbRead = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

    if (!ReadFile(hFile, pv, cb, pcbRead, NULL))
        return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Peek(void *pv, ULONG cb, ULONG *pcbRead)
{
    HRESULT hr = Read(pv, cb, pcbRead);
    if (FAILED(hr))
        return hr;

    // signed distance
    LONG distance = *pcbRead;

    if (SetFilePointer(hFile, -distance, NULL, FILE_CURRENT)
            == INVALID_SET_FILE_POINTER)
        return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT FileStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
    *pcbWritten = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

    if (!WriteFile(hFile, pv, cb, pcbWritten, NULL))
        return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}

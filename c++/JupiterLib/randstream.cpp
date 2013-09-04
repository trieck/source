/////////////////////////////////////////////////////////////////////////////
//
//	RANDSTREAM.CPP : random access file based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "RandStream.h"

/////////////////////////////////////////////////////////////////////////////
RandomFileStream::RandomFileStream()
	: hFile(INVALID_HANDLE_VALUE), m_cRef(0)
{
	// The constructor AddRef's
	AddRef();
}

/////////////////////////////////////////////////////////////////////////////
RandomFileStream::~RandomFileStream()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
RandomFileStream *RandomFileStream::Create(LPCSTR lpFileName,
        DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes)
{
	RandomFileStream *pStream = new RandomFileStream();
	if (!pStream->Open(lpFileName, dwDesiredAccess, dwShareMode,
	                   dwCreationDisposition, dwFlagsAndAttributes)) {
		pStream->Release();
		return NULL;
	}

	return pStream;
}

/////////////////////////////////////////////////////////////////////////////
BOOL RandomFileStream::Open(LPCSTR lpFileName, DWORD dwDesiredAccess,
                            DWORD dwShareMode, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
{
	Close();
	hFile = CreateFile(lpFileName, dwDesiredAccess, dwShareMode, NULL,
	                   dwCreationDisposition, dwFlagsAndAttributes, NULL);
	return hFile != INVALID_HANDLE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////
void RandomFileStream::Close()
{
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
ULONG RandomFileStream::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
ULONG RandomFileStream::Release()
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::QueryInterface(REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown)
		*ppv = this;
	if (riid == IID_IStream || riid == IID_ISequentialStream)
		*ppv = this;

	if (*ppv) {
		((LPUNKNOWN)*ppv)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
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
HRESULT RandomFileStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
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

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin,
                               ULARGE_INTEGER *plibNewPosition)
{
	DWORD dwMoveMethod;

	switch (dwOrigin) {
	case STREAM_SEEK_SET:
		dwMoveMethod = FILE_BEGIN;
		break;
	case STREAM_SEEK_CUR:
		dwMoveMethod = FILE_CURRENT;
		break;
	case STREAM_SEEK_END:
		dwMoveMethod = FILE_END;
		break;
	default:
		return STG_E_INVALIDFUNCTION;
		break;
	}

	if (SetFilePointerEx(hFile, dlibMove, (PLARGE_INTEGER)plibNewPosition,
	                     dwMoveMethod) == 0)
		return HRESULT_FROM_WIN32(GetLastError());

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::SetSize(ULARGE_INTEGER libNewSize)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::CopyTo(IStream *pstm, ULARGE_INTEGER cb,
                                 ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Commit(DWORD grfCommitFlags)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Revert()
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::LockRegion(ULARGE_INTEGER libOffset,
                                     ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::UnlockRegion(ULARGE_INTEGER libOffset,
                                       ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
	if (GetFileSizeEx(hFile, (PLARGE_INTEGER) &pstatstg->cbSize) == 0)
		return HRESULT_FROM_WIN32(GetLastError());
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT RandomFileStream::Clone(IStream **ppstm)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
STDMETHODIMP RandomFileStream::Tell(ULARGE_INTEGER *pPosition)
{
	if (pPosition == NULL)
		return E_POINTER;

	(*pPosition).QuadPart = 0;

	LARGE_INTEGER curr;
	curr.QuadPart = 0;
	if (SetFilePointerEx(hFile, curr, (PLARGE_INTEGER)pPosition,
	                     FILE_CURRENT) == 0)
		return HRESULT_FROM_WIN32(GetLastError());

	return S_OK;
}
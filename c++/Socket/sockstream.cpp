/////////////////////////////////////////////////////////////////////////////
//
//	SOCKSTREAM.CPP : socket based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include <winsock2.h>
#include "SockStream.h"

/////////////////////////////////////////////////////////////////////////////
SockStream::SockStream(SOCKET s)
	: m_sock(s), m_cRef(0)
{
	// The constructor AddRef's
	AddRef();
}

/////////////////////////////////////////////////////////////////////////////
SockStream::~SockStream()
{
}

/////////////////////////////////////////////////////////////////////////////
SockStream * SockStream::Create(SOCKET s)
{
	return new SockStream(s);
}

/////////////////////////////////////////////////////////////////////////////
ULONG SockStream::AddRef()
{
	return ++m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
ULONG SockStream::Release()
{
	if (--m_cRef == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::QueryInterface(REFIID riid, LPVOID *ppv)
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
HRESULT SockStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	return Recv(pv, cb, pcbRead, 0);
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::Peek(void *pv, ULONG cb, ULONG *pcbRead)
{
	return Recv(pv, cb, pcbRead, MSG_PEEK);
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::Recv(void *pv, ULONG cb, ULONG *pcbRead, int flags)
{
	*pcbRead = 0;

	if (!pv)
		return STG_E_INVALIDPOINTER;

	if (cb == 0)
		return S_OK;

	*pcbRead = recv(m_sock, (LPSTR)pv, cb, flags);
	if (*pcbRead == SOCKET_ERROR)
		return E_FAIL;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
	*pcbWritten = 0;

	if (!pv)
		return STG_E_INVALIDPOINTER;

	if (cb == 0)
		return S_OK;

	*pcbWritten = send(m_sock, (LPCSTR)pv, cb, 0);
	if (*pcbWritten == SOCKET_ERROR)
		return E_FAIL;

	return S_OK;
}

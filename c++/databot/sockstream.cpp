/////////////////////////////////////////////////////////////////////////////
//
// SOCKSTREAM.CPP : socket based sequential stream class
//
// Copyright(c) 2008, KnowX.com, All Rights Reserved
//

#include "common.h"
#include <winsock2.h>
#include <atlbase.h>
#include "socket.h"
#include "sockstream.h"

/////////////////////////////////////////////////////////////////////////////
SockStream::SockStream() 
 : m_cRef(0)
{
    AddRef();	// not externally creatable
}

/////////////////////////////////////////////////////////////////////////////
SockStream::~SockStream()
{
}

/////////////////////////////////////////////////////////////////////////////
ULONG SockStream::AddRef(void)
{
    return ++m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
ULONG SockStream::Release(void)
{
	if (--m_cRef == 0) {
		delete this;
		return 0;
	}

	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::QueryInterface(REFIID riid, void** ppv)
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
HRESULT SockStream::Read(void *pv, ULONG cb, ULONG* pcbRead)
{
    if (pcbRead)
        *pcbRead = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

	if ((*pcbRead = sock.read(pv, cb)) == SOCKET_ERROR) {
		*pcbRead = 0;
		return HRESULT_FROM_WIN32(GetLastError());
	}

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT SockStream::Write(const void *pv, ULONG cb, ULONG* pcbWritten)
{
	if (pcbWritten)
		*pcbWritten = 0;

    if (!pv)
        return STG_E_INVALIDPOINTER;

    if (cb == 0)
        return S_OK;

	if ((*pcbWritten = sock.write(pv, cb)) == SOCKET_ERROR) {
		*pcbWritten = 0;
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
SockStream *SockStream::Create(LPCSTR host, uint16_t port)
{
	SockStream *pStream = new SockStream();

	pStream->sock.connect(host, port);	// may fail

	return pStream;
}
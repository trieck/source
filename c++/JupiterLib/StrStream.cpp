/////////////////////////////////////////////////////////////////////////////
//
//	STRSTREAM.CPP : Peekable string stream
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "StrStream.h"

/////////////////////////////////////////////////////////////////////////////
StrStream::StrStream()
		: m_cRef(1), m_Pos(0), m_Size(0), m_Buf(0)	// new creation only
{
	alloc();
}

/////////////////////////////////////////////////////////////////////////////
StrStream* StrStream::newInstance()
{
	return new StrStream();
}

/////////////////////////////////////////////////////////////////////////////
StrStream::~StrStream()
{
	free();
}

/////////////////////////////////////////////////////////////////////////////
HRESULT StrStream::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == IID_ISequentialStream || riid == IID_IUnknown) {
		*ppvObject = static_cast<ISequentialStream*>(this);
		static_cast<LPUNKNOWN>(*ppvObject)->AddRef();	// pointer copied
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

/////////////////////////////////////////////////////////////////////////////
ULONG StrStream::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
ULONG StrStream::Release(void)
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT StrStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	ULONG n = min(avail(), cb);
	memcpy(pv, &m_Buf[m_Pos], n);
	m_Pos += n;
	*pcbRead = n;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT StrStream::Peek(void *pv, ULONG cb, ULONG *pcbRead)
{
	ULONG n = min(avail(), cb);
	memcpy(pv, &m_Buf[m_Pos], n);
	*pcbRead = n;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT StrStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
	*pcbWritten = 0;

	ULONG n = min(avail(), cb);
	if (n == 0 && !resize(m_Size + cb)) {
		return E_OUTOFMEMORY;	// no space
	}
	if (n == 0) {
		n = min(avail(), cb);
	}

	memcpy(&m_Buf[m_Pos], pv, n);
	m_Pos += n;
	*pcbWritten = n;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT StrStream::Write(LPCSTR pstr)
{
	ULONG written;
	return Write(pstr, strlen(pstr), &written);
}

/////////////////////////////////////////////////////////////////////////////
void StrStream::alloc()
{
	m_Buf = (LPBYTE)malloc(m_Size = 0);
}

/////////////////////////////////////////////////////////////////////////////
bool StrStream::resize(ULONG cb)
{
	m_Buf = (LPBYTE)realloc(m_Buf, m_Size = cb);
	return m_Buf != NULL;
}

/////////////////////////////////////////////////////////////////////////////
void StrStream::free()
{
	if (m_Buf != 0) {
		::free(m_Buf);
		m_Buf = 0;
	}
}
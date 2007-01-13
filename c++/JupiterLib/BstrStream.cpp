/////////////////////////////////////////////////////////////////////////////
// 
//	BSTRSTREAM.CPP : BSTR peekable stream
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "BstrStream.h"
  
/////////////////////////////////////////////////////////////////////////////
BstrStream::BstrStream()
 : m_cRef(1), m_Pos(0), m_Size(0), m_Buf(0)	// new creation only
{
	alloc();
}

/////////////////////////////////////////////////////////////////////////////
BstrStream* BstrStream::newInstance()
{
	return new BstrStream();
}

/////////////////////////////////////////////////////////////////////////////
BstrStream::~BstrStream()
{
	free();
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::QueryInterface(REFIID riid, void **ppvObject)
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
ULONG BstrStream::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

/////////////////////////////////////////////////////////////////////////////
ULONG BstrStream::Release(void)
{
	if (InterlockedDecrement(&m_cRef) == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}
    	
/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	ULONG n = min(avail(), cb);
	memcpy(pv, &m_Buf[m_Pos], n);
	m_Pos += n;
	*pcbRead = n;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::Peek(void *pv, ULONG cb, ULONG *pcbRead)
{
	ULONG n = min(avail(), cb);
	memcpy(pv, &m_Buf[m_Pos], n);
	*pcbRead = n;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
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
HRESULT BstrStream::Write(LPCSTR pstr)
{
	wstring wstr = ansi2uni(pstr);
	return Write(wstr.c_str());
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::Write(LPCOLESTR pstr)
{
	BSTR bstr = SysAllocString(pstr);
	HRESULT hr = WriteBstr(bstr);
	SysFreeString(bstr);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::WriteBstr(BSTR bstr)
{
	UINT nlen = SysStringByteLen(bstr);
	ULONG written = 0, pos = 0, cb = nlen;
	HRESULT hr;

	LPBYTE pbuf = (LPBYTE)bstr;
	for ( ; pos < nlen; cb -= written, pos += written) {
		hr = Write(&pbuf[pos], cb, &written);
		if (FAILED(hr)) return hr;		
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT BstrStream::ReadBstr(BSTR *bstr)
{
	*bstr = SysAllocStringByteLen(NULL, avail());
	UINT nlen = SysStringByteLen(*bstr);

	ULONG read = 0, pos = 0, cb = nlen;
	HRESULT hr;

	LPBYTE pbuf = (LPBYTE)*bstr;
	for ( ; pos < nlen; cb -= read, pos += read) {
		hr = Read(&pbuf[pos], cb, &read);
		if (FAILED(hr)) {
			SysFreeString(*bstr);
			return hr;
		}
		if (read == 0) break;
	}

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
void BstrStream::alloc()
{
	m_Buf = (LPBYTE)CoTaskMemAlloc(m_Size = 0);	
}

/////////////////////////////////////////////////////////////////////////////
bool BstrStream::resize(ULONG cb)
{
	m_Buf = (LPBYTE)CoTaskMemRealloc(m_Buf, m_Size = cb);
	return m_Buf != NULL;
}

/////////////////////////////////////////////////////////////////////////////
void BstrStream::free()
{
	if (m_Buf != 0) {
		CoTaskMemFree(m_Buf);
		m_Buf = 0;
	}
}
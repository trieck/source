/////////////////////////////////////////////////////////////////////////////
//
//	BSTRSTREAM.H : BSTR peekable stream
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __BSTRSTREAM_H__
#define __BSTRSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class BstrStream : public IPeekableStream {
// Construction / Destruction
private:
	BstrStream();
public:
	~BstrStream();

// Interface
	virtual STDMETHODIMP QueryInterface(REFIID riid,
	                                    void **ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef(void);

	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual STDMETHODIMP Read(void *pv, ULONG cb,
	                          ULONG *pcbRead);

	virtual STDMETHODIMP Write(const void *pv, ULONG cb,
	                           ULONG *pcbWritten);

	virtual STDMETHODIMP Peek(void *pv, ULONG cb,
	                          ULONG *pcbRead);

	void Reset() {
		m_Pos = 0;
	}

	static BstrStream *newInstance();
	HRESULT Write(LPCSTR pstr);
	HRESULT Write(LPCOLESTR pstr);
	HRESULT WriteBstr(BSTR bstr);
	HRESULT ReadBstr(BSTR *bstr);

// Implementation
private:
	void alloc();
	bool resize(ULONG cb);
	void free();
	ULONG avail() const {
		return m_Size - m_Pos;
	}

	LPBYTE m_Buf;	// Buffer
	LONG m_cRef;	// Reference count
	ULONG m_Pos;	// Read / Write pointer
	ULONG m_Size;	// Size in bytes of stream
};
/////////////////////////////////////////////////////////////////////////////

#endif // __BSTRSTREAM_H__

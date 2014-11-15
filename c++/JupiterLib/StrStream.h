/////////////////////////////////////////////////////////////////////////////
//
//	STRSTREAM.H : Peekable string stream
//
//	Copyright (c) 2006 Thomas A. Rieck, All Rights Reserved
//

#ifndef __STRSTREAM_H__
#define __STRSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class StrStream : public IPeekableStream {
// Construction / Destruction
private:
    StrStream();
public:
    ~StrStream();

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

    static StrStream *newInstance();
    HRESULT Write(LPCSTR pstr);

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

#endif // __STRSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
//
//	SOCKSTREAM.H : socket based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SOCKSTREAM_H__
#define __SOCKSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class SockStream : public IPeekableStream {
// Construction / Destruction
private:
    SockStream(SOCKET s);
public:
    virtual ~SockStream();

// Interface
    static SockStream *Create(SOCKET s);

    // inherited methods
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);

    STDMETHODIMP Read(/* [out] */ void __RPC_FAR *pv, /* [in]  */ ULONG cb,
                                  /* [out] */ ULONG __RPC_FAR *pcbRead);
    STDMETHODIMP Peek(/* [out] */ void __RPC_FAR *pv, /* [in]  */ ULONG cb,
                                  /* [out] */ ULONG __RPC_FAR *pcbRead);
    STDMETHODIMP Write(/* [in] */ const void __RPC_FAR *pv, /* [in] */ ULONG cb,
                                  /* [out]*/ ULONG __RPC_FAR *pcbWritten);

// Implementation
private:
    HRESULT Recv(void *pv, ULONG cb, ULONG *pcbRead, int flags);

    ULONG m_cRef;	// reference count
    SOCKET m_sock;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __SOCKSTREAM_H__
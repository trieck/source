/////////////////////////////////////////////////////////////////////////////
//
// SOCKSTREAM.H : Socket based sequential stream class
//
// Copyright(c) 2008, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SOCKSTREAM_H__
#define __SOCKSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class SockStream : public ISequentialStream
{
// Construction / Destruction
protected:
	SockStream();
public:
    virtual ~SockStream();

// Interface
	STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    
    STDMETHODIMP Read(/* [out] */ void __RPC_FAR *pv, /* [in]  */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
	STDMETHODIMP Write(/* [in] */ const void __RPC_FAR *pv, /* [in] */ 
		ULONG cb, /* [out]*/ ULONG __RPC_FAR *pcbWritten);

	static SockStream *SockStream::Create(LPCSTR host, uint16_t port);

// Implementation
private:
	ULONG m_cRef;	// reference count
	Socket sock;	// underlying socket
};
/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<SockStream> SockStreamPtr;

#endif // __SOCKSTREAM_H__
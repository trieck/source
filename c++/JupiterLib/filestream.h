/////////////////////////////////////////////////////////////////////////////
//
//	FILESTREAM.H : file based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class FileStream : public IPeekableStream
{
// Construction / Destruction
private:
    FileStream();
public:
    virtual ~FileStream();

// Interface
    static FileStream *Create(LPCSTR lpFileName,
                              DWORD dwDesiredAccess,
                              DWORD dwShareMode,
                              DWORD dwCreationDisposition,
                              DWORD dwFlagsAndAttributes);

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
    BOOL Open(LPCSTR lpFileName, DWORD dwDesiredAccess,
              DWORD dwShareMode, DWORD dwCreationDisposition,
              DWORD dwFlagsAndAttributes);

    void Close();

    ULONG m_cRef;	// reference count
    HANDLE hFile;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __FILESTREAM_H__
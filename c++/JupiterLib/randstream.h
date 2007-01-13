/////////////////////////////////////////////////////////////////////////////
//
//	RANDSTREAM.H : random access file based stream class
//	NOTE: NOT externally creatable
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __RANDSTREAM_H__
#define __RANDSTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class RandomFileStream : public IStream
{
// Construction / Destruction
private:
	RandomFileStream();
public:
	virtual ~RandomFileStream();

// Interface
	static RandomFileStream *Create(LPCSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		DWORD dwCreationDisposition,
		DWORD dwFlagsAndAttributes);

	// inherited methods
	STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    
    STDMETHODIMP Read(void *pv, ULONG cb,
            ULONG *pcbRead);

	STDMETHODIMP Write(const void *pv, ULONG cb,
            ULONG *pcbWritten);

	STDMETHODIMP Seek(LARGE_INTEGER dlibMove,
            DWORD dwOrigin,
            ULARGE_INTEGER *plibNewPosition);
        
	STDMETHODIMP SetSize(ULARGE_INTEGER libNewSize);
        
	STDMETHODIMP CopyTo(IStream *pstm,
            ULARGE_INTEGER cb,
            ULARGE_INTEGER *pcbRead,
            ULARGE_INTEGER *pcbWritten);
        
	STDMETHODIMP Commit(DWORD grfCommitFlags);
        
	STDMETHODIMP Revert();
        
	STDMETHODIMP LockRegion(ULARGE_INTEGER libOffset,
            ULARGE_INTEGER cb, DWORD dwLockType);
        
	STDMETHODIMP UnlockRegion(ULARGE_INTEGER libOffset,
            ULARGE_INTEGER cb, DWORD dwLockType);
        
	STDMETHODIMP Stat(STATSTG *pstatstg, DWORD grfStatFlag);
        
	STDMETHODIMP Clone(IStream **ppstm);

	// New methods
	STDMETHODIMP Tell(ULARGE_INTEGER *pPosition);

// Implementation
private:
	BOOL Open(LPCSTR lpFileName, DWORD dwDesiredAccess,
		DWORD dwShareMode, DWORD dwCreationDisposition, 
		DWORD dwFlagsAndAttributes);

	void Close();

	LONG m_cRef;	// reference count
	HANDLE hFile;
};
/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<RandomFileStream> RandomFileStreamPtr;

#endif // __RANDSTREAM_H__
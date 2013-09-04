/////////////////////////////////////////////////////////////////////////////
//
// FILESTREAM.H : Buffered sequential file stream class
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__

/////////////////////////////////////////////////////////////////////////////
class FileStream : public ISequentialStream {
// Construction / Destruction
public:
	FileStream();
	virtual ~FileStream();

// Interface
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);

	STDMETHODIMP Read(/* [out] */ void __RPC_FAR *pv, /* [in]  */ ULONG cb,
	                              /* [out] */ ULONG __RPC_FAR *pcbRead);
	STDMETHODIMP Write(/* [in] */ const void __RPC_FAR *pv, /* [in] */ ULONG cb,
	                              /* [out]*/ ULONG __RPC_FAR *pcbWritten);

	STDMETHODIMP Close();
	STDMETHODIMP GetFileSize(PLARGE_INTEGER pFileSize);

	static FileStream *FileStream::Create(LPCTSTR lpFileName,
	                                      DWORD dwDesiredAccess, DWORD dwShareMode,
	                                      DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes);

// Implementation
private:
	BOOL Open(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
	          DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes);
	BOOL ReadBlock();
	BOOL WriteBlock();
	void Alloc();
	void Free();

	uint8_t *m_buf;			// buffer
	uint8_t *m_pbuf;		// buffer pointer
	uint32_t m_nbuf;		// number of bytes in the buffer
	ULONG m_cRef;			// reference count
	tstring m_FileName;		// file name
	DWORD m_Access;			// desired access
	DWORD m_ShareMode;		// share mode
	DWORD m_Disposition;	// creation disposition
	DWORD m_Flags;			// file creation flags
	DWORD m_BlockSize;		// size of a block
	HANDLE m_hFile;			// file handle
};

/////////////////////////////////////////////////////////////////////////////

typedef CComPtr<FileStream> FileStreamPtr;

#endif // __FILESTREAM_H__
/////////////////////////////////////////////////////////////////////////////
//
//	FILEMAP.H : Windows file mapping interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __FILEMAP_H__
#define __FILEMAP_H__

/////////////////////////////////////////////////////////////////////////////
class FileMapping {
// Construction / Destruction
public:
	FileMapping();
	virtual ~FileMapping();

// Interface
	bool Create(LPCTSTR lpszFilename, DWORD dwDesiredAccess,
	            DWORD dwShareMode, DWORD dwCreationDisposition,
	            DWORD dwFlagsAndAttributes, DWORD dwProtect);
	void Close();

	LPVOID MapView(DWORD access, uint64_t offset, uint32_t nbytes);
	bool UnmapView();
	bool FlushView(uint32_t nbytes);

// Implementation
private:
	HANDLE m_hFile;     // file handle
	HANDLE m_hMapping;	// mapping handle
	LPVOID m_pView;     // mapped view
};
/////////////////////////////////////////////////////////////////////////////

#endif // __FILEMAP_H__
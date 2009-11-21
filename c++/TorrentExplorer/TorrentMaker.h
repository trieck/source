// TorrentMaker.h: interface for the TorrentMaker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORRENTMAKER_H__6663A791_F9BD_40F3_A0E2_D7060F62EE62__INCLUDED_)
#define AFX_TORRENTMAKER_H__6663A791_F9BD_40F3_A0E2_D7060F62EE62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TorrentMaker {
public:
	TorrentMaker(ICallable *pCallable = NULL, CFile *pFile = NULL);
	virtual ~TorrentMaker();

public:
	// Make from dictionary object
	void Make(LPDICTIONARY d);

	// Parameterized make
	void Make(const CString &files,
	          const CStringVec &trackers,
	          const CString &comment,
	          DWORD pieceSize,
	          BOOL m_Private);

	void DoCancel();
	BOOL DidCancel() const {
		return m_Cancel;
	}

	CFile *GetFile() {
		return &m_file;
	}

private:
	void BeginDictionary();
	void BeginList();
	void BeginInteger();
	void EndObject();

	void WriteTrackers(const CStringVec &trackers);
	void WriteInfo();
	void WriteFiles();
	void WriteFileList();
	void WriteFile(LPCSTR filename);
	void WritePieces();
	void NotifyTotalPieces();

	void WritePair(const CString &k, LPTORRENTOBJECT v);
	void WritePair(const CString &k, const CString &v);
	void WritePair(const CString &k, const CTime &v);
	void WritePair(const CString &k, __int64 i);

	void WriteObject(LPTORRENTOBJECT e);
	void WriteDict(LPDICTIONARY d);
	void WriteList(LPLIST l);
	void WriteString(const CString &s);
	void WriteRawString(const CString &s);
	void WriteInt(__int64 i);
	void WriteRawInt(__int64 i);
	void WriteChar(char c);

	void Recurse(const CString &path);
	void AddFile(LPCSTR filename);
	__int64 GetFileLength(LPCSTR filename);
	CString GetShortName(LPCSTR filename);

	void HashFiles();
	BOOL GetNextPiece(LPSTR piece);
	void CloseCurrentFile();
	BOOL OpenNextFile();
	DWORD Read(LPSTR pbuf, int nlen);

	CMemFile m_file, m_pieces;	// memory based files
	CFile *m_pFile;				// file to write to
	CString m_Files;			// source path
	CStringVec m_FileList;		// list of expanded files
	DWORD m_pieceSize;			// piece size
	BOOL m_Private;				// private torrent

	HANDLE m_hFile;				// current file handle
	int m_currentFile;			// current file index
	ICallable *m_pCallable;		// callback interface ptr
	__int64 m_TotalLength;		// total length of all files
	BOOL m_Cancel;				// user has cancelled flag
};

#endif // !defined(AFX_TORRENTMAKER_H__6663A791_F9BD_40F3_A0E2_D7060F62EE62__INCLUDED_)

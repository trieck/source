// TorrentMaker.cpp: implementation of the TorrentMaker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "TorrentObject.h"
#include "Dictionary.h"
#include "String.h"
#include "Integer.h"
#include "List.h"
#include "TorrentMaker.h"
#include "SHA1.h"
#include "resource.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <math.h>

#define MAX_FILES (1000)

static char BEGIN_DICT[1] =    { 'd' };
static char BEGIN_LIST[1] =    { 'l' };
static char BEGIN_INTEGER[1] = { 'i' };
static char END_OBJECT[1] =    { 'e' };

namespace {	// anonymous

CString basename(LPCSTR path);
CString filename(LPCSTR path);
CStringVec SplitPath(LPCSTR path);

}	// anonymous

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
TorrentMaker::TorrentMaker(ICallable *pCallable, CFile *pFile)
	: m_hFile(INVALID_HANDLE_VALUE), m_currentFile(-1),
	  m_pCallable(pCallable), m_TotalLength(0), m_Cancel(FALSE)
{
	// use memory based file if not supplied for writing
	m_pFile = pFile == NULL ? &m_file : pFile;
}

//////////////////////////////////////////////////////////////////////
TorrentMaker::~TorrentMaker()
{
	CloseCurrentFile();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::CloseCurrentFile()
{
	if (m_hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::Make(LPDICTIONARY d)
{
	m_pFile->SeekToBegin();		// rewind for writing
	WriteDict(d);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::Make(const CString &files,
                        const CStringVec &trackers, const CString &comment,
                        DWORD pieceSize, BOOL priv)
{
	m_Files = files;
	m_pieceSize = pieceSize;
	m_Private = priv;
	m_FileList.erase(m_FileList.begin(), m_FileList.end());

	CloseCurrentFile();

	// Rewind for writing
	m_pFile->SeekToBegin();

	BeginDictionary();					// begin dictionary

	WriteTrackers(trackers);

	if (comment.GetLength()) WritePair("comment", comment);
	WritePair("created by", "Torrent Explorer/1000");
	WritePair("creation date", CTime::GetCurrentTime());
	WritePair("encoding", "UTF-8");

	WriteInfo();

	EndObject();						// end dictionary

	// Rewind for reading
	m_pFile->SeekToBegin();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::DoCancel()
{
	m_Cancel = TRUE;
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::BeginDictionary()
{
	m_pFile->Write(BEGIN_DICT, sizeof(BEGIN_DICT));
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::BeginList()
{
	m_pFile->Write(BEGIN_LIST, sizeof(BEGIN_LIST));
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::BeginInteger()
{
	m_pFile->Write(BEGIN_INTEGER, sizeof(BEGIN_INTEGER));
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::EndObject()
{
	m_pFile->Write(END_OBJECT, sizeof(END_OBJECT));
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteTrackers(const CStringVec &trackers)
{
	if (trackers.size() == 0) return;

	WritePair("announce", trackers[0]);

	if (trackers.size() > 1) {	// list of backup trackers included
		WriteString("announce-list");

		// stored as a list of lists
		BeginList();
		BeginList();

		CStringVec::const_iterator it = trackers.begin();
		for ( ; it != trackers.end(); it++) {
			WriteString(*it);
		}

		EndObject();
		EndObject();
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteInfo()
{
	WriteString("info");

	BeginDictionary();

	WriteFiles();
	NotifyTotalPieces();

	WritePair("piece length", m_pieceSize);
	WritePieces();

	if (m_Private) WritePair("private", 1);

	EndObject();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::NotifyTotalPieces()
{
	// callback with the total number of pieces
	if (m_pCallable) {
		DWORD totalPieces = (DWORD)(m_TotalLength / m_pieceSize);
		m_pCallable->Call(totalPieces);
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WritePieces()
{
	WriteString("pieces");

	HashFiles();

	CString buf;
	int nlength = (int)m_pieces.GetLength();
	m_pieces.Read(buf.GetBufferSetLength(nlength), nlength);

	WriteString(buf);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::HashFiles()
{
	m_pieces.SeekToBegin();

	char digest[SHA1_DIGEST_SIZE];
	while (GetNextPiece(digest)) {
		if (m_Cancel) break;

		m_pieces.Write(digest, SHA1_DIGEST_SIZE);
		if (m_pCallable)
			m_pCallable->Call(0);
		PumpMessages();
	}

	m_pieces.SeekToBegin();
}

//////////////////////////////////////////////////////////////////////
BOOL TorrentMaker::GetNextPiece(LPSTR piece)
{
	CString s;

	LPSTR buf = s.GetBuffer(m_pieceSize);

	DWORD read = Read(buf, m_pieceSize);

	s.ReleaseBuffer(read);

	if (read == 0)
		return FALSE;

	SHA1 sha1(s);
	memcpy(piece, (LPCSTR)sha1, SHA1_DIGEST_SIZE);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
DWORD TorrentMaker::Read(LPSTR pbuf, int nlen)
{
	DWORD read, total = 0, chunk_size = nlen;

	for (;;) {
		if (total == nlen)
			break;

		if (m_hFile == INVALID_HANDLE_VALUE)
			if (!OpenNextFile())
				break;

		BOOL b = ReadFile(m_hFile, pbuf, chunk_size, &read, NULL);
		if (!b && GetLastError() != ERROR_HANDLE_EOF) {
			ThrowUserException(IDS_CANTREADFROMFILE);
		}

		if (read == 0) {					// EOF
			if (!OpenNextFile())
				break;
		} else if (read != chunk_size) {	// whole chunk not read
			chunk_size = chunk_size - read;
			pbuf += read;
		}
		total += read;
	}

	return total;
}

//////////////////////////////////////////////////////////////////////
BOOL TorrentMaker::OpenNextFile()
{
	CloseCurrentFile();

	if (m_currentFile == m_FileList.size() - 1)
		return FALSE;	// no more files

	CString filename = m_FileList[++m_currentFile];

	m_hFile = CreateFile(filename,
	                     GENERIC_READ,
	                     0,
	                     NULL,
	                     OPEN_EXISTING,
	                     FILE_ATTRIBUTE_NORMAL,
	                     NULL);
	if (m_hFile == INVALID_HANDLE_VALUE) {
		ThrowUserException(IDS_CANTOPENFILE, filename);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteFiles()
{
	DWORD attr = GetFileAttributes(m_Files);
	if (attr & FILE_ATTRIBUTE_DIRECTORY) {
		Recurse(m_Files);	// build the list of files
		WriteString("files");
		BeginList();
		WriteFileList();
		EndObject();
		WritePair("name", basename(m_Files));
	} else {
		AddFile(m_Files);
		WritePair("name", filename(m_Files));
		m_TotalLength = GetFileLength(m_Files);
		WritePair("length", m_TotalLength);
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteFileList()
{
	if (m_FileList.size() == 0) {	// no files
		ThrowUserException(IDS_NOFILES);
	}

	CStringVec::const_iterator it = m_FileList.begin();
	for ( ; it != m_FileList.end(); it++) {
		WriteFile(*it);
	}
}

//////////////////////////////////////////////////////////////////////
__int64 TorrentMaker::GetFileLength(LPCSTR filename)
{
	struct _stati64 buf;
	if (_stati64(filename, &buf) == -1)
		return 0;

	return buf.st_size;
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteFile(LPCSTR filename)
{
	BeginDictionary();

	CString shortFile = GetShortName(filename);
	__int64 length = GetFileLength(filename);
	m_TotalLength += length;

	WritePair("length", length);
	WriteString("path");

	BeginList();
	CStringVec path = SplitPath(shortFile);
	CStringVec::const_iterator it = path.begin();
	for ( ; it != path.end(); it++) {
		WriteString(*it);
	}
	EndObject();

	EndObject();
}

//////////////////////////////////////////////////////////////////////
CString TorrentMaker::GetShortName(LPCSTR filename)
{
	LPCSTR pfiles(m_Files);

	while (*filename == *pfiles) {
		filename++;
		pfiles++;
	}

	if (filename[0] == '\\' || filename[0] == '/')
		filename++;

	return filename;
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::Recurse(const CString &path)
{
	CFileFind finder;

	CString pattern(path), fpath;
	pattern += "\\*";

	BOOL found = finder.FindFile(pattern);
	while (found) {
		found = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory()) {
			fpath = finder.GetFilePath();
			Recurse(fpath);
		} else {
			fpath = finder.GetFilePath();
			AddFile(fpath);
		}
	}

	finder.Close();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::AddFile(LPCSTR filename)
{
	if (m_FileList.size() == MAX_FILES) {
		ThrowUserException(IDS_TOOMANYFILES, MAX_FILES);
	}
	m_FileList.push_back(filename);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WritePair(const CString &k, LPTORRENTOBJECT v)
{
	WriteString(k);
	WriteObject(v);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WritePair(const CString &k, __int64 v)
{
	WriteString(k);
	WriteInt(v);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WritePair(const CString &k, const CTime &v)
{
	WriteString(k);
	WriteInt(v.GetTime());
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WritePair(const CString &k, const CString &v)
{
	WriteString(k);
	WriteString(v);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteObject(LPTORRENTOBJECT e)
{
	switch (e->GetElementType()) {
	case ET_DICT:
		WriteDict((LPDICTIONARY)e);
		break;
	case ET_LIST:
		WriteList((LPLIST)e);
		break;
	case ET_INTEGER:
		WriteInt(*(LPINTEGER)e);
		break;
	case ET_STRING:
		WriteString(*(LPSTRING)e);
		break;
	}
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteDict(LPDICTIONARY d)
{
	BeginDictionary();					// begin dictionary

	LPTORRENTOBJECT v;
	KeyVec keys = d->GetKeysSorted();
	KeyVec::const_iterator it = keys.begin();
	for ( ; it != keys.end(); it++) {
		v = d->Get(*it);
		WritePair(*it, v);
	}

	EndObject();						// end dictionary
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteList(LPLIST l)
{
	BeginList();

	for (UINT i = 0; i < l->size(); i++) {
		WriteObject(l->GetAt(i));
	}

	EndObject();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteString(const CString &s)
{
	WriteRawInt(s.GetLength());
	WriteChar(':');
	WriteRawString(s);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteInt(__int64 i)
{
	BeginInteger();
	WriteRawInt(i);
	EndObject();
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteRawString(const CString &s)
{
	int nlength = s.GetLength();
	for (int i = 0; i < nlength; i++)
		WriteChar(s.GetAt(i));
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteRawInt(__int64 i)
{
	CString s;
	_i64toa(i, s.GetBuffer(50), 10);
	s.ReleaseBuffer();
	WriteRawString(s);
}

//////////////////////////////////////////////////////////////////////
void TorrentMaker::WriteChar(char c)
{
	m_pFile->Write(&c, sizeof(char));
}

namespace {	// anonymous

//////////////////////////////////////////////////////////////////////
CString basename(LPCSTR path)
{
	char file[_MAX_FNAME] = { 0 };
	_splitpath(path, NULL, NULL, file, NULL);
	return file;
}

//////////////////////////////////////////////////////////////////////
CString filename(LPCSTR path)
{
	char file[_MAX_FNAME] = { 0 };
	char ext[_MAX_EXT] = { 0 };
	char output[_MAX_FNAME + _MAX_EXT + 1];

	_splitpath(path, NULL, NULL, file, ext);

	sprintf(output, "%s%s", file, ext);

	return output;
}

//////////////////////////////////////////////////////////////////////
CStringVec SplitPath(LPCSTR path)
{
	CStringVec output;
	CString buf;

	while (*path) {
		if (path[0] == '\\' || path[0] == '/') {
			if (buf.GetLength() != 0) {
				output.push_back(buf);
				buf.Empty();
			}
		} else {
			buf += *path;
		}
		path++;
	}

	if (buf.GetLength() != 0)
		output.push_back(buf);

	return output;
}

}	// anonymous
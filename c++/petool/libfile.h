/////////////////////////////////////////////////////////////////////////////
//
//	LIBFILE.H : Library file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __LIBFILE_H__
#define __LIBFILE_H__

/////////////////////////////////////////////////////////////////////////////
class LibraryFile {
// Construction / Destruction
public:
	LibraryFile();
	virtual ~LibraryFile();

// Interface
	void Dump(LPVOID lpBase);

// Implementation
private:
	void DumpArchiveMemberHeader(PIMAGE_ARCHIVE_MEMBER_HEADER
	                             pArchHeader, DWORD fileOffset);
	void DumpImportLibraryRecord(IMPORT_OBJECT_HEADER *pImpObjHdr);
	void DumpFirstLinkerMember(PVOID p);
	void DumpSecondLinkerMember(PVOID p);
	void DumpLongnamesMember(PVOID p, DWORD len);

	PSTR m_pszLongNames;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __LIBFILE_H__
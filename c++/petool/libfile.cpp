/////////////////////////////////////////////////////////////////////////////
//
//	LIBFILE.CPP : Library file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "libfile.h"
#include "objfile.h"
#include "filemap.h"

/////////////////////////////////////////////////////////////////////////////
LibraryFile::LibraryFile() : m_pszLongNames(NULL)
{
}

/////////////////////////////////////////////////////////////////////////////
LibraryFile::~LibraryFile()
{
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::Dump(LPVOID pBase)
{
    PIMAGE_ARCHIVE_MEMBER_HEADER pArchHeader =
        MAKE_PTR(PIMAGE_ARCHIVE_MEMBER_HEADER, pBase,
                 IMAGE_ARCHIVE_START_SIZE);

    bool bSawFirstLinkerMember = false;
    bool bSawSecondLinkerMember = false;

    while (pArchHeader) {
        if (memcmp(pArchHeader->EndHeader, IMAGE_ARCHIVE_END, 2) != 0)
            break;  // bail out if we don't see EndHeader signature

        DumpArchiveMemberHeader(pArchHeader, MAKE_PTR_OFFSET(pArchHeader, pBase));

        // Check if it's one of the new (NT4,SP3)
        // import library records.  If this doesn't compile for you, you
        // can #ifdef them out.
        IMPORT_OBJECT_HEADER *pImpObjHdr = (IMPORT_OBJECT_HEADER *)(pArchHeader+1);
        if ((pImpObjHdr->Sig1 == IMAGE_FILE_MACHINE_UNKNOWN)
                && (pImpObjHdr->Sig2 == IMPORT_OBJECT_HDR_SIG2)) {
            DumpImportLibraryRecord(pImpObjHdr);
        }
        if (memcmp(pArchHeader->Name, IMAGE_ARCHIVE_LINKER_MEMBER, 16) == 0) {
            if (!bSawFirstLinkerMember) {
                DumpFirstLinkerMember((PVOID)(pArchHeader + 1));
                bSawFirstLinkerMember = true;
            } else if (!bSawSecondLinkerMember) {
                DumpSecondLinkerMember((PVOID)(pArchHeader + 1));
                bSawSecondLinkerMember = true;
            }
        } else if (memcmp(pArchHeader->Name, IMAGE_ARCHIVE_LONGNAMES_MEMBER, 16) == 0) {
            DumpLongnamesMember((PVOID)(pArchHeader + 1),
                                atoi((char *)pArchHeader->Size));
        } else {    // It's an OBJ file
            ObjectFile::Dump((PIMAGE_FILE_HEADER)(pArchHeader + 1));
        }

        DWORD dwSize = atoi((char *)pArchHeader->Size)
                       + IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR;
        dwSize = (dwSize+1) & ~1; // Round up

        // Get a pointer to the next archive member
        pArchHeader = MAKE_PTR(PIMAGE_ARCHIVE_MEMBER_HEADER, pArchHeader,
                               dwSize);
    }
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::DumpArchiveMemberHeader(PIMAGE_ARCHIVE_MEMBER_HEADER
        pArchHeader, DWORD fileOffset)
{
    _tprintf(_T("Archive Member Header (%08X):\n"), fileOffset);

    _tprintf(_T("  Name:     %.16S\n"), pArchHeader->Name);
    if (pArchHeader->Name[0] == _T('/') && isdigit(pArchHeader->Name[1])) {
        _tprintf(_T("  (%S)\n"), m_pszLongNames + atoi((PSTR)pArchHeader->Name+1));
    }

    time_t T;
    sscanf((LPCSTR)(pArchHeader->Date), "%I64d", &T);

    UINT64 size;
    sscanf((LPCSTR)pArchHeader->Size, "%I64d", &size);

    _tprintf(_T("  Date:     %s"),  _tctime(&T));

    if (pArchHeader->UserID[0] != ' ') {
        _tprintf(_T("  UserID:   %.6S\n"), pArchHeader->UserID);
    }
    if (pArchHeader->GroupID[0] != ' ') {
        _tprintf(_T("  GroupID:  %.6S\n"), pArchHeader->GroupID);
    }
    if (pArchHeader->Mode[0] != ' ') {
        _tprintf(_T("  Mode:     %.8S\n"), pArchHeader->Mode);
    }
    _tprintf(_T("  Size:     %.10s\n"), Comma(size).c_str());
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::DumpImportLibraryRecord(IMPORT_OBJECT_HEADER *pImpObjHdr)
{
    _tprintf(_T("  Import Library Record:\n"));
    _tprintf(_T("  Version: %u  Machine: %X  TimeDate: %08X  SizeOfData:%u\n"),
             pImpObjHdr->Version, pImpObjHdr->Machine,
             pImpObjHdr->TimeDateStamp, pImpObjHdr->SizeOfData);

    if (pImpObjHdr->NameType & IMPORT_OBJECT_ORDINAL)
        _tprintf(_T("  Ordinal: %u\n"), pImpObjHdr->Ordinal);
    else
        _tprintf(_T("  Hint: %u\n"), pImpObjHdr->Hint);

#define CASE_STRING(x) case x: s = _T(#x); break;

    LPCTSTR s = _T("");

    switch(pImpObjHdr->Type) {
        CASE_STRING(IMPORT_OBJECT_CODE)
        CASE_STRING(IMPORT_OBJECT_DATA)
        CASE_STRING(IMPORT_OBJECT_CONST)
    }
    _tprintf(_T("  Type: %s (%u)\n"), s, pImpObjHdr->Type);

    s = _T("");
    switch(pImpObjHdr->NameType) {
        CASE_STRING(IMPORT_OBJECT_ORDINAL)
        CASE_STRING(IMPORT_OBJECT_NAME)
        CASE_STRING(IMPORT_OBJECT_NAME_NO_PREFIX)
        CASE_STRING(IMPORT_OBJECT_NAME_UNDECORATE)
    }
    _tprintf(_T("  NameType: %s (%u)\n"), s, pImpObjHdr->NameType);

    PSTR pszSymName = (PSTR)(pImpObjHdr+1);
    PSTR pszDllName = pszSymName + strlen(pszSymName)+1;

    _tprintf(_T("  Symbol: %S\n"), pszSymName);
    _tprintf(_T("  DLL:    %S\n\n\n"), pszDllName);
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::DumpFirstLinkerMember(PVOID p)
{
    DWORD dwSymbols = *(PDWORD)p;
    PDWORD pdwOffsets = MAKE_PTR(PDWORD, p, sizeof(DWORD));
    PSTR pSymbolName;

    dwSymbols = SwapByteOrder(dwSymbols);
    pSymbolName = MAKE_PTR(PSTR, pdwOffsets, sizeof(DWORD) * dwSymbols);

    _tprintf(_T("First Linker Member:\n"));
    _tprintf(_T("  Symbols:         %08X\n"), dwSymbols);
    _tprintf(_T("  MbrOffs   Name\n  --------  ----\n"));

    DWORD offset;
    for (DWORD i = 0; i < dwSymbols; i++ ) {
        offset = SwapByteOrder(*pdwOffsets);
        _tprintf(_T("  %08X  %S\n"), offset, pSymbolName);

        pdwOffsets++;
        pSymbolName += strlen(pSymbolName) + 1;
    }
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::DumpSecondLinkerMember(PVOID p)
{
    DWORD dwArchiveMembers = *(PDWORD)p;
    PDWORD pdwOffsets = MAKE_PTR(PDWORD, p, sizeof(DWORD));
    DWORD dwSymbols;
    PSTR pSymbolName;
    PWORD pIndices;

    // The number of symbols is in the DWORD right past the end of the
    // member offset array.
    dwSymbols = pdwOffsets[dwArchiveMembers];

    pIndices = MAKE_PTR(PWORD, p,
                        sizeof(DWORD) + dwArchiveMembers * sizeof(DWORD) + sizeof(DWORD));

    pSymbolName = MAKE_PTR(PSTR, pIndices, dwSymbols * sizeof(WORD) );

    _tprintf(_T("Second Linker Member:\n"));

    _tprintf(_T("  Archive Members: %08X\n"), dwArchiveMembers);
    _tprintf(_T("  Symbols:         %08X\n"), dwSymbols);
    _tprintf(_T("  MbrOffs   Name\n  --------  ----\n"));

    for (DWORD i = 0; i < dwSymbols; i++) {
        _tprintf(_T("  %08X  %S\n"), pdwOffsets[pIndices[i] - 1], pSymbolName);
        pSymbolName += strlen(pSymbolName) + 1;
    }
}

/////////////////////////////////////////////////////////////////////////////
void LibraryFile::DumpLongnamesMember(PVOID p, DWORD len)
{
    PSTR pszName = (PSTR)p;
    DWORD cbString, offset = 0;

    m_pszLongNames = (PSTR)p;	// Save off pointer for use when dumping
    // out OBJ member names

    _tprintf(_T("Longnames:\n"));

    while (offset < len) {
        cbString = strlen(pszName)+1;

        _tprintf(_T("  %05u: %S\n"), offset, pszName);
        offset += cbString;
        pszName += cbString;
    }

    _tprintf(_T("\n"));
}

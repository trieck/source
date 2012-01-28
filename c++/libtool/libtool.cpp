// libtool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "filemap.h"
#include "objfile.h"
#include <time.h>

namespace {     // anonymous

/////////////////////////////////////////////////////////////////////////////
void Usage()
{
    tcerr << TEXT("usage: libtool archive") << endl;
    exit(1);
}

/////////////////////////////////////////////////////////////////////////////
void DumpArchiveMemberHeader(PIMAGE_ARCHIVE_MEMBER_HEADER pArchHeader,
    DWORD fileOffset)
{
    _tprintf(_T("Archive Member Header (%08X):\n"), fileOffset);

    _tprintf(_T("  Name:     %.16S\n"), pArchHeader->Name);
    if (pArchHeader->Name[0] == _T('/') && isdigit(pArchHeader->Name[1])) {
        // _tprintf(_T("  (%s)\n"), PszLongnames + _ttoi((TCHAR*)pArchHeader->Name+1));
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
void DumpFirstLinkerMember(PVOID p)
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
void DumpSecondLinkerMember(PVOID p)
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
void DumpLib(LPCTSTR library)
{
    FileMapping mapping;
    if (!mapping.Create(library, GENERIC_READ, FILE_SHARE_READ, 
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, PAGE_READONLY)) {
            throw Exception(LastError());
    }

    LPVOID pBase;
    if ((pBase = mapping.MapView(FILE_MAP_READ, 0, 0)) == NULL) {
        throw Exception(_T("Unable to map view of file."));
    }

    if (memcmp(pBase,IMAGE_ARCHIVE_START, IMAGE_ARCHIVE_START_SIZE)) {
        throw Exception(_T("Not a valid .LIB file - signature not found\n"));
    }

    PIMAGE_ARCHIVE_MEMBER_HEADER pArchHeader = 
        MAKE_PTR(PIMAGE_ARCHIVE_MEMBER_HEADER, pBase, 
            IMAGE_ARCHIVE_START_SIZE);

    bool bSawFirstLinkerMember = false;
    bool bSawSecondLinkerMember = false;

    while (pArchHeader) {
        if (memcmp(pArchHeader->EndHeader, IMAGE_ARCHIVE_END, 2) != 0)
            break;  // bail out if we don't see EndHeader signature

        DumpArchiveMemberHeader(pArchHeader, MAKE_PTR_OFFSET(pArchHeader, pBase));
        
        if (memcmp(pArchHeader->Name, IMAGE_ARCHIVE_LINKER_MEMBER, 16) == 0) {
            if (!bSawFirstLinkerMember) {
            DumpFirstLinkerMember((PVOID)(pArchHeader + 1));
            bSawFirstLinkerMember = true;
            } else if (!bSawSecondLinkerMember) {
                DumpSecondLinkerMember((PVOID)(pArchHeader + 1));
                bSawSecondLinkerMember = true;
            }
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

}   // anonymous

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 2) {
        Usage();
    }

    try {
        DumpLib(argv[1]);
    } catch (const _com_error &e) {
        tcerr << e.Description() << endl;
    } catch (const Exception &e) {
        tcerr << e.GetDescription() << endl;
        return 1;
    }

	return 0;
}


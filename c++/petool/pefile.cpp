/////////////////////////////////////////////////////////////////////////////
//
//	PEFILE.CPP : PE file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "pecommon.h"
#include "pefile.h"
#include "libfile.h"
#include "objfile.h"
#include "filemap.h"

/////////////////////////////////////////////////////////////////////////////
PEFile::PEFile()
{
}

/////////////////////////////////////////////////////////////////////////////
PEFile::~PEFile()
{
}

/////////////////////////////////////////////////////////////////////////////
void PEFile::Dump(LPCTSTR filename)
{
    FileMapping mapping;
    if (!mapping.Create(filename, GENERIC_READ, FILE_SHARE_READ, 
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, PAGE_READONLY)) {
            throw Exception(LastError());
    }

    LPVOID pBase;
    if ((pBase = mapping.MapView(FILE_MAP_READ, 0, 0)) == NULL) {
        throw Exception(_T("Unable to map view of file."));
    }

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pBase;
	PIMAGE_FILE_HEADER pImgFileHdr = (PIMAGE_FILE_HEADER)pBase;

	if (pDosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
        throw Exception(_T(".EXE format not supported."));
    } else if (PECommon::IsValidMachineType(pImgFileHdr->Machine)) {
		if (pImgFileHdr->SizeOfOptionalHeader == 0)	{	// 0 optional header
			ObjectFile::Dump(pImgFileHdr);				// means it's an OBJ			
		} else {
			throw Exception(_T("Unrecognized file format."));
		}
    } else if (memcmp(pBase, IMAGE_ARCHIVE_START, 
		IMAGE_ARCHIVE_START_SIZE) == 0) {
		LibraryFile archive;
		archive.Dump(pBase);
	} else {
		throw Exception(_T("Unrecognized file format."));
	}
}

/////////////////////////////////////////////////////////////////////////////
//
//	OBJFILE.CPP : Object file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "objfile.h"
#include "pecommon.h"

/////////////////////////////////////////////////////////////////////////////
ObjectFile::ObjectFile()
{
}

/////////////////////////////////////////////////////////////////////////////
ObjectFile::~ObjectFile()
{
}

/////////////////////////////////////////////////////////////////////////////
void ObjectFile::Dump(PIMAGE_FILE_HEADER pImageFileHeader)
{
    PECommon::DumpHeader(pImageFileHeader);

    _tprintf(_T("\n"));

    PIMAGE_SECTION_HEADER pSections = 
        MAKE_PTR(PIMAGE_SECTION_HEADER, (pImageFileHeader+1), 
            pImageFileHeader->SizeOfOptionalHeader);

    PECommon::DumpSectionTable(pSections, pImageFileHeader->NumberOfSections, FALSE);
}


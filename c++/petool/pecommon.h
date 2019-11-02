/////////////////////////////////////////////////////////////////////////////
//
//	PECOMMON.H : Common PE file format definitions
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __PECOMMON_H__
#define __PECOMMON_H__

namespace PECommon
{

/////////////////////////////////////////////////////////////////////////////
bool IsValidMachineType(WORD wMachineType);
void DumpHeader(PIMAGE_FILE_HEADER pImageFileHeader);
void DumpSectionTable(PIMAGE_SECTION_HEADER section, UINT nSections,
                      BOOL IsEXE);
} // PECommon


#endif // __PECOMMON_H__

/////////////////////////////////////////////////////////////////////////////
//
//	PECOMMON.H : Common PE file format definitions
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "pecommon.h"

namespace PECommon {  

typedef struct {
    WORD    flag;
    PTSTR    name;
} WORD_FLAG_DESCRIPTIONS;

typedef struct {
    DWORD   flag;
    PTSTR    name;
} DWORD_FLAG_DESCRIPTIONS;

/////////////////////////////////////////////////////////////////////////////
// Bitfield values and names for the IMAGE_FILE_HEADER flags
WORD_FLAG_DESCRIPTIONS ImageFileHeaderCharacteristics[] = {
    { IMAGE_FILE_RELOCS_STRIPPED, _T("RELOCS_STRIPPED") },
    { IMAGE_FILE_EXECUTABLE_IMAGE, _T("EXECUTABLE_IMAGE") },
    { IMAGE_FILE_LINE_NUMS_STRIPPED, _T("LINE_NUMS_STRIPPED") },
    { IMAGE_FILE_LOCAL_SYMS_STRIPPED, _T("LOCAL_SYMS_STRIPPED") },
    { IMAGE_FILE_AGGRESIVE_WS_TRIM, _T("AGGRESIVE_WS_TRIM") },
    { IMAGE_FILE_BYTES_REVERSED_LO, _T("BYTES_REVERSED_LO") },
    { IMAGE_FILE_32BIT_MACHINE, _T("32BIT_MACHINE") },
    { IMAGE_FILE_DEBUG_STRIPPED, _T("DEBUG_STRIPPED") },
    { IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP, _T("REMOVABLE_RUN_FROM_SWAP") },
    { IMAGE_FILE_NET_RUN_FROM_SWAP, _T("NET_RUN_FROM_SWAP") },
    { IMAGE_FILE_SYSTEM, _T("SYSTEM") },
    { IMAGE_FILE_DLL, _T("DLL") },
    { IMAGE_FILE_UP_SYSTEM_ONLY, _T("UP_SYSTEM_ONLY") },
    { IMAGE_FILE_BYTES_REVERSED_HI, _T("BYTES_REVERSED_HI") }
};

#define NUMBER_IMAGE_HEADER_FLAGS \
    (sizeof(ImageFileHeaderCharacteristics) / sizeof(WORD_FLAG_DESCRIPTIONS))

DWORD_FLAG_DESCRIPTIONS SectionCharacteristics[] = {
    { IMAGE_SCN_TYPE_NO_PAD, _T("NO_PAD") },
    { IMAGE_SCN_CNT_CODE, _T("CODE") },
    { IMAGE_SCN_CNT_INITIALIZED_DATA, _T("INITIALIZED_DATA") },
    { IMAGE_SCN_CNT_UNINITIALIZED_DATA, _T("UNINITIALIZED_DATA") },
    { IMAGE_SCN_LNK_OTHER, _T("OTHER") },
    { IMAGE_SCN_LNK_INFO, _T("INFO") },
    { IMAGE_SCN_LNK_REMOVE, _T("REMOVE") },
    { IMAGE_SCN_LNK_COMDAT, _T("COMDAT") },
    { IMAGE_SCN_MEM_FARDATA, _T("FARDATA") },
    { IMAGE_SCN_MEM_PURGEABLE, _T("PURGEABLE") },
    { IMAGE_SCN_MEM_LOCKED, _T("LOCKED") },
    { IMAGE_SCN_MEM_PRELOAD, _T("PRELOAD") },
    { IMAGE_SCN_LNK_NRELOC_OVFL, _T("NRELOC_OVFL") },
    { IMAGE_SCN_MEM_DISCARDABLE, _T("DISCARDABLE") },
    { IMAGE_SCN_MEM_NOT_CACHED, _T("NOT_CACHED") },
    { IMAGE_SCN_MEM_NOT_PAGED, _T("NOT_PAGED") },
    { IMAGE_SCN_MEM_SHARED, _T("SHARED") },
    { IMAGE_SCN_MEM_EXECUTE, _T("EXECUTE") },
    { IMAGE_SCN_MEM_READ, _T("READ") },
    { IMAGE_SCN_MEM_WRITE, _T("WRITE") },
};

#define NUMBER_SECTION_CHARACTERISTICS \
    (sizeof(SectionCharacteristics) / sizeof(DWORD_FLAG_DESCRIPTIONS))
/////////////////////////////////////////////////////////////////////////////
LPCTSTR GetMachineTypeName(WORD wMachineType)
{
    switch(wMachineType) {        
        case IMAGE_FILE_MACHINE_I386: 	return _T("i386");
        case IMAGE_FILE_MACHINE_R3000:  return _T("R3000");
		case 160:                       return _T("R3000 big endian");
        case IMAGE_FILE_MACHINE_R4000:  return _T("R4000");
		case IMAGE_FILE_MACHINE_R10000: return _T("R10000");
        case IMAGE_FILE_MACHINE_ALPHA:  return _T("Alpha");
        case IMAGE_FILE_MACHINE_POWERPC:return _T("PowerPC");
        case IMAGE_FILE_MACHINE_AMD64:  return _T("AMD64 (K8)");
        default:    					return _T("unknown");
    }
}

/////////////////////////////////////////////////////////////////////////////
void DumpHeader(PIMAGE_FILE_HEADER pImageFileHeader)
{
    UINT headerFieldWidth = 30;
    
    time_t timestamp = pImageFileHeader->TimeDateStamp;

    _tprintf(_T("File Header:\n"));

    _tprintf(_T("  %-*s%04X (%s)\n"), headerFieldWidth, _T("Machine:"), 
        pImageFileHeader->Machine,
        GetMachineTypeName(pImageFileHeader->Machine));
    _tprintf(_T("  %-*s%04X\n"), headerFieldWidth, _T("Number of Sections:"),
        pImageFileHeader->NumberOfSections);
    _tprintf(_T("  %-*s%08X -> %s"), headerFieldWidth, _T("TimeDateStamp:"),
        pImageFileHeader->TimeDateStamp,
        _tctime(&timestamp));
    _tprintf(_T("  %-*s%08X\n"), headerFieldWidth, _T("PointerToSymbolTable:"),
        pImageFileHeader->PointerToSymbolTable);
    _tprintf(_T("  %-*s%08X\n"), headerFieldWidth, _T("NumberOfSymbols:"),
        pImageFileHeader->NumberOfSymbols);
    _tprintf(_T("  %-*s%04X\n"), headerFieldWidth, _T("SizeOfOptionalHeader:"),
        pImageFileHeader->SizeOfOptionalHeader);
    _tprintf(_T("  %-*s%04X\n"), headerFieldWidth, _T("Characteristics:"),
        pImageFileHeader->Characteristics);

    for (UINT i = 0; i < NUMBER_IMAGE_HEADER_FLAGS; i++) {
        if (pImageFileHeader->Characteristics & 
            ImageFileHeaderCharacteristics[i].flag)
            _tprintf(_T("    %s\n"), ImageFileHeaderCharacteristics[i].name);
    }
}

/////////////////////////////////////////////////////////////////////////////
void DumpSectionTable(PIMAGE_SECTION_HEADER section, UINT nSections, 
    BOOL IsEXE)
{
    LPCTSTR pszAlign;

    _tprintf(_T("Section Table\n"));
    
    for (UINT i = 1; i <= nSections; i++, section++) {
        _tprintf(_T("  %02X %-8.8S  %s: %08X  VirtAddr:  %08X\n"),
                i, section->Name,
                IsEXE ? _T("VirtSize") : _T("PhysAddr"),
                section->Misc.VirtualSize, section->VirtualAddress);
        _tprintf(_T("    raw data offs:   %08X  raw data size: %08X\n"),
                section->PointerToRawData, section->SizeOfRawData );
        _tprintf(_T("    relocation offs: %08X  relocations:   %08X\n"),
                section->PointerToRelocations, section->NumberOfRelocations );
        _tprintf(_T("    line # offs:     %08X  line #'s:      %08X\n"),
                section->PointerToLinenumbers, section->NumberOfLinenumbers );
        _tprintf(_T("    characteristics: %08X\n"), section->Characteristics);
        _tprintf(_T("    "));

        for (UINT j = 0; j < NUMBER_SECTION_CHARACTERISTICS; j++) {
            if (section->Characteristics & 
                SectionCharacteristics[j].flag )
                _tprintf( _T("  %s"), SectionCharacteristics[j].name );
        }
		
		switch( section->Characteristics & IMAGE_SCN_ALIGN_64BYTES) {
			case IMAGE_SCN_ALIGN_1BYTES: pszAlign = _T("ALIGN_1BYTES"); break;
			case IMAGE_SCN_ALIGN_2BYTES: pszAlign = _T("ALIGN_2BYTES"); break;
			case IMAGE_SCN_ALIGN_4BYTES: pszAlign = _T("ALIGN_4BYTES"); break;
			case IMAGE_SCN_ALIGN_8BYTES: pszAlign = _T("ALIGN_8BYTES"); break;
			case IMAGE_SCN_ALIGN_16BYTES: pszAlign = _T("ALIGN_16BYTES"); break;
			case IMAGE_SCN_ALIGN_32BYTES: pszAlign = _T("ALIGN_32BYTES"); break;
			case IMAGE_SCN_ALIGN_64BYTES: pszAlign = _T("ALIGN_64BYTES"); break;
			default: pszAlign = _T("ALIGN_DEFAULT(16)"); break;
		}

		_tprintf( _T("  %s\n\n"), pszAlign);
    }
}

}   // PECommon

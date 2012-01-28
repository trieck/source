/////////////////////////////////////////////////////////////////////////////
//
//	OBJFILE.H : Object file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __OBJFILE_H__
#define __OBJFILE_H__

/////////////////////////////////////////////////////////////////////////////
class ObjectFile
{
// Construction / Destruction
public:
	ObjectFile();
	virtual ~ObjectFile();

// Interface    
    static void Dump(PIMAGE_FILE_HEADER pImageFileHeader);

// Implementation
private:
    static void DumpHeader(PIMAGE_FILE_HEADER pImageFileHeader);

};
/////////////////////////////////////////////////////////////////////////////

#endif // __OBJFILE_H__
/////////////////////////////////////////////////////////////////////////////
//
//	PEFILE.H : PE file interface
//
//	Copyright(c) 2012 Thomas A. Rieck, All Rights Reserved
//

#ifndef __PEFILE_H__
#define __PEFILE_H__

/////////////////////////////////////////////////////////////////////////////
class PEFile
{
// Construction / Destruction
public:
    PEFile();
    virtual ~PEFile();

// Interface
    static void Dump(LPCTSTR filename);

// Implementation
private:
};
/////////////////////////////////////////////////////////////////////////////

#endif // __PEFILE_H__

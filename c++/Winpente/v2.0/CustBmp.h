/*---------------------------------------
	Module Name	:	CustBmp.h
	Author		:	Thomas A. Rieck
	Purpose		:	Custom Bitmap
					Drawing Declarations
	Date		:	08/31/1997
---------------------------------------*/

#ifndef __CUSTBMP_H__
#define __CUSTBMP_H__

///////////////////////////////////////////////////////////////////
// The CCustomBitmap class

class CCustomBitmap : public CObject {
public:
    CCustomBitmap();
    virtual ~CCustomBitmap();
protected:
    HPALETTE			CreateDIBPalette(LPBITMAPINFO, LPINT);
public:
    VOID				PaintDCByHBitmap(CDC*, HBITMAP, BOOL);
    VOID				PaintDCByResource(CDC*, INT);
    VOID				PaintDCByColor(CDC*, COLORREF);
    HBITMAP				LoadResourceBitmap(INT, HPALETTE*);

    DECLARE_DYNCREATE(CCustomBitmap)
};

///////////////////////////////////////////////////////////////////

#endif	// __CUSTBMP_H__
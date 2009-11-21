//////////////////////////////////////////////////////
//	Module	:	BMLOC.H								//
//	Purpose	:	custom bitmap functions (local)		//
//	Author	:	Thomas A. Rieck						//
//	Date	:	4/5/97								//
//////////////////////////////////////////////////////

#ifndef __BMLOC_H__
#define __BMLOC_H__

#include <windows.h>
#include <io.h>

// local functions
int AssertValidBitmap(LPSTR szFileName);
int AssertDevCapable(HWND hWnd, INT nFlags);
HBITMAP CreateBitmapFromFile(HDC hDC, LPSTR szFileName);
BOOL CALLBACK DlgProc(	HWND  hwndDlg,	// handle to dialog box
                       UINT  uMsg,		// message
                       WPARAM  wParam,	// first message parameter
                       LPARAM  lParam);
int ExtractBMInfo(LPSTR szFileName, LPBITMAPFILEHEADER pBMFH, LPBITMAPINFO* ppBMI, LPVOID* ppBits);
void FillDlgInfo(HWND hDlg, LPSTR szFileName, BITMAPFILEHEADER bmfh, LPBITMAPINFO pBMI);
LONG ScanAlign (LONG pWidth);
void StripBits (LPBITMAPINFO pBMI, LPBYTE pBits, UINT nColor);
#endif	// __BM_LOC_H__
//////////////////////////////////////////////////////
//	Module	:	BMEXP.C								//
//	Purpose	:	custom bitmap functions	(exported)	//
//	Author	:	Thomas A. Rieck						//
//	Date	:	4/5/97								//
//////////////////////////////////////////////////////

#include "bmmain.h"
#include "bmloc.h"
#include "bmexp.h"
#include "resource.h"

///////////////////////
// GetBitmapSize
DllExport DWORD WINAPI GetBitmapSize (LPSTR szFileName)
{
	// find the file size in bytes
	HFILE hFile;
	DWORD dwCount;

	hFile = _lopen(szFileName, OF_READ);
	if (hFile == HFILE_ERROR)
		return (0);

	dwCount = GetFileSize((HANDLE)hFile, NULL);

	_lclose(hFile);

	return (dwCount);
}

///////////////////////
// PaintWindow
DllExport DWORD WINAPI PaintWindow(HWND hWnd, COLORREF lColor)
{
	RECT rc;
	HDC hDC;
	HBRUSH hBrush, hBrushOld;

	// get DC for window client area
	hDC = GetDC(hWnd);

	// get clip box
	GetClipBox(hDC, &rc);

	// create brush
	if (!(hBrush = CreateSolidBrush(lColor)))
		return (0);

	// select into DC
	hBrushOld= SelectObject(hDC, hBrush);

	// paint brush into DC
	if (!(PatBlt(hDC, rc.left, rc.top, rc.right, rc.bottom, PATCOPY)))
		return (0);

	// select original brush into DC
	SelectObject(hDC, hBrushOld);

	// delete brush
	DeleteObject(hBrush);

	// release DC
	ReleaseDC(hWnd, hDC);

	return(1);
}

////////////////////
// ExtractBMFH
DllExport DWORD WINAPI ExtractBMFH(LPSTR szFileName, LPBITMAPFILEHEADER pBMFH)
{
	HFILE hFile;
	BITMAPFILEHEADER bmfh;
	DWORD dwCount;

	// initialize structure
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));

	// open file
	hFile = _lopen(szFileName, OF_READ) ;
	if (hFile == HFILE_ERROR)
		return (0);

	// extract BITMAPFILEHEADER structure from file
	dwCount = _lread(hFile, &bmfh, sizeof(BITMAPFILEHEADER));

	// close file
	_lclose(hFile);

	if (dwCount == HFILE_ERROR)
		return(0);
	else {
		// copy data into structure
		memcpy(pBMFH, &bmfh, sizeof(BITMAPFILEHEADER));
		return (1);
	}
}

/////////////////////
// ExtractBMI
DllExport DWORD WINAPI ExtractBMI(LPSTR szFileName, LPBITMAPINFO pBMI)
{
	HFILE hFile;
	BITMAPINFOHEADER bmih;
	DWORD dwCount;

	// open file
	hFile = _lopen(szFileName, OF_READ) ;
	if (hFile == HFILE_ERROR)
		return (0);

	// move past BITMAPFILEHEADER
	dwCount = SetFilePointer ((HANDLE)hFile, sizeof(BITMAPFILEHEADER), NULL, FILE_BEGIN);

	if (dwCount == HFILE_ERROR) {
		_lclose(hFile);
		return (0);
	}

	// extract BITMAPINFOHEADER structure
	dwCount = _lread(hFile, &bmih, sizeof(BITMAPINFOHEADER));

	if (dwCount == HFILE_ERROR) {
		_lclose(hFile);
		return(0);
	} else {
		// copy data into structure
		memcpy(pBMI, &bmih, sizeof(BITMAPINFOHEADER));

		// check for 24-bit bitmap
		if (bmih.biBitCount != 24)
			_lread(hFile, pBMI->bmiColors, (1 << bmih.biBitCount) * sizeof(RGBQUAD));

		_lclose(hFile);
		return (1);
	}
}

////////////////////
// BlastBitmapFile
DllExport DWORD WINAPI BlastBitmapFile(HWND hWnd, LPSTR szFileName, LPPOINT pPoint)
{
	HBITMAP hBitmap;
	BITMAP bm;
	HDC hDC, hDCMem;

	hDC = GetDC(hWnd);

	if ((hBitmap = CreateBitmapFromFile(hDC, szFileName))) {
		// paint the bitmap
		hDCMem = CreateCompatibleDC(hDC);
		SelectObject(hDCMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &bm);
		BitBlt(hDC, pPoint->x, pPoint->y, bm.bmWidth, bm.bmHeight,
		       hDCMem, 0, 0, SRCCOPY);

		// clean up
		DeleteDC(hDCMem);
		ReleaseDC(hWnd, hDC);
		DeleteObject(hBitmap);
		return (1);
	} else {
		ReleaseDC(hWnd, hDC);
		return (0);
	}
}

////////////////////
// StretchBitmapFile
DllExport DWORD WINAPI StretchBitmapFile(HWND hWnd, LPSTR szFileName)
{
	HBITMAP hBitmap;
	BITMAP bm;
	HDC hDC, hDCMem;
	RECT rc;

	hDC = GetDC(hWnd);

	if ((hBitmap = CreateBitmapFromFile(hDC, szFileName))) {
		// paint and stretch the bitmap
		hDCMem = CreateCompatibleDC(hDC);
		SelectObject(hDCMem, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &bm);

		GetClientRect(hWnd, &rc);

		StretchBlt(hDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
		           hDCMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		// clean up
		DeleteDC(hDCMem);
		ReleaseDC(hWnd, hDC);
		DeleteObject(hBitmap);
		return (1);
	} else {
		ReleaseDC(hWnd, hDC);
		return (0);
	}
}

//////////////////
// GetBitSize
DllExport DWORD WINAPI GetBitSize(LPSTR szFileName)
{
	HFILE hFile;
	BITMAPFILEHEADER bmfh;

	hFile = _lopen(szFileName, OF_READ);
	if (hFile == HFILE_ERROR)
		return (0);

	// load BITMAPFILEHEADER structure
	_lread(hFile, &bmfh, sizeof(BITMAPFILEHEADER));

	// close file
	_lclose(hFile);

	return (bmfh.bfSize - bmfh.bfOffBits);
}

//////////////////
// GetBMBits
DllExport DWORD WINAPI GetBMBits(LPSTR szFileName, LPBYTE pBits)
{
	HFILE hFile;
	BITMAPINFOHEADER bmih;
	DWORD dwCount;

	// open file
	hFile = _lopen(szFileName, OF_READ) ;
	if (hFile == HFILE_ERROR)
		return (0);

	// move past BITMAPFILEHEADER
	SetFilePointer ((HANDLE)hFile, sizeof(BITMAPFILEHEADER), NULL, FILE_BEGIN);

	// read BITMAPINFOHEADER
	_lread(hFile, &bmih, sizeof(BITMAPINFOHEADER));

	// move past the color table.
	if (bmih.biBitCount != 24)
		SetFilePointer ((HANDLE)hFile, (1<<bmih.biBitCount) * sizeof(RGBQUAD), NULL, FILE_CURRENT);

	// read bitmap data
	dwCount = _lread(hFile, pBits, bmih.biSizeImage);

	// close file
	_lclose(hFile);

	return (dwCount);
}

////////////////////
// BlastBitmap
DllExport DWORD WINAPI BlastBitmap(HWND hWnd, LPBITMAPINFO lpBMI,
                                   LPVOID pBits, LPPOINT pPoint)
{
	HDC hDC;
	DWORD dwCount;

	hDC = GetDC(hWnd);

	dwCount = SetDIBitsToDevice(hDC, pPoint->x, pPoint->y, lpBMI->bmiHeader.biWidth, lpBMI->bmiHeader.biHeight,
	                            0,0,0,lpBMI->bmiHeader.biHeight, pBits, lpBMI, DIB_RGB_COLORS);

	ReleaseDC(hWnd, hDC);
	return (dwCount);
}

////////////////////
// StretchBitmap
DllExport DWORD WINAPI StretchBitmap(HWND hWnd, LPBITMAPINFO lpBMI,
                                     LPVOID pBits, LPPOINT pPoint)
{
	HDC hDC;
	DWORD dwCount;
	RECT rc;

	hDC = GetDC(hWnd);

	// get client rectangle
	GetClientRect(hWnd, &rc);

	// set stretch blt mode
	SetStretchBltMode(hDC, COLORONCOLOR);

	// stretch the bits
	dwCount = StretchDIBits(hDC, pPoint->x, pPoint->y, (rc.right - rc.left), (rc.bottom - rc.top), 0, 0, lpBMI->bmiHeader.biWidth, lpBMI->bmiHeader.biHeight,
	                        pBits, lpBMI, DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(hWnd, hDC);

	return (dwCount);
}

///////////////
// GetBMISize
DllExport DWORD WINAPI GetBMISize(LPSTR szFileName)
{
	HFILE hFile;
	BITMAPINFOHEADER bmih;
	DWORD dwSize, dwCount;

	// open file
	hFile = _lopen(szFileName, OF_READ) ;
	if (hFile == HFILE_ERROR)
		return (0);

	// move past BITMAPFILEHEADER
	dwCount = SetFilePointer ((HANDLE)hFile, sizeof(BITMAPFILEHEADER), NULL, FILE_BEGIN) ;

	if (dwCount == HFILE_ERROR) {
		_lclose(hFile);
		return (0);
	}

	// load BITMAPINFOHEADER structure
	dwCount = _lread(hFile, &bmih, sizeof(BITMAPINFOHEADER));
	if (dwCount == HFILE_ERROR) {
		_lclose(hFile);
		return (0);
	}

	// find BMI size; check for 24 bit BM
	if (bmih.biBitCount == 24)
		dwSize = sizeof(BITMAPINFOHEADER);
	else
		dwSize = sizeof(BITMAPINFOHEADER) + ((1<<bmih.biBitCount) * sizeof(RGBQUAD));

	_lclose(hFile);

	return (dwSize);
}

//////////////////
// ShowBitmapInfo
DWORD WINAPI ShowBitmapInfo(HWND hwndParent, LPSTR szFileName)
{
	int nRtn;
	char szBuffer[255];

	// check for valid bitmap
	if (!(AssertValidBitmap(szFileName))) {
		LoadString(hInstance, IDS_INVALIDBITMAP, szBuffer, 255);
		MessageBox(hwndParent, szBuffer, "Error", MB_ICONEXCLAMATION | MB_OK);
		return (0L);
	}

	// check for valid window handle
	if (hwndParent == NULL || hwndParent == GetDesktopWindow())
		return(0L);

	nRtn = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_BMINFO), hwndParent, DlgProc, (LPARAM)szFileName);

	return (nRtn ? 1L : 0L);
}
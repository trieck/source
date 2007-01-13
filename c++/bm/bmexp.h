//////////////////////////////////////////////////////	
//	Module	:	BMEXP.H								//
//	Purpose	:	custom bitmap functions (exported)	//
//	Author	:	Thomas A. Rieck						//
//	Date	:	4/5/97								//
//////////////////////////////////////////////////////

#ifndef __BMEXP_H__
#define __BMEXP_H__

#include <windows.h>
#include <io.h>
#include <stdio.h>

// macro for dll exports in Win32
#define DllExport	__declspec(dllexport)

// exported functions
DllExport DWORD WINAPI GetBitmapSize (LPSTR szFileName);
DllExport DWORD WINAPI PaintWindow(HWND hWnd, COLORREF lColor);
DllExport DWORD WINAPI ExtractBMFH(LPSTR szFileName, LPBITMAPFILEHEADER pBMFH);
DllExport DWORD WINAPI ExtractBMI(LPSTR szFileName, LPBITMAPINFO pBMI);
DllExport DWORD WINAPI BlastBitmapFile(HWND hWnd, LPSTR szFileName, LPPOINT pPoint);
DllExport DWORD WINAPI BlastBitmap(HWND hWnd, LPBITMAPINFO lpBMI, LPVOID pBits, LPPOINT pPoint);
DllExport DWORD WINAPI StretchBitmapFile(HWND hWnd, LPSTR szFileName);
DllExport DWORD WINAPI StretchBitmap(HWND hWnd, LPBITMAPINFO lpBMI, LPVOID pBits, LPPOINT pPoint);
DllExport DWORD WINAPI GetBitSize(LPSTR szFileName);
DllExport DWORD WINAPI GetBMBits(LPSTR szFileName, LPBYTE pBits);
DllExport DWORD WINAPI GetBMISize(LPSTR szFileName);
DllExport DWORD WINAPI ShowBitmapInfo(HWND hwndParent, LPSTR szFileName);

#endif	// __BM_EXP_H__
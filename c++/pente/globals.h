
#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// Global helper functions

#ifdef _ENABLE_LOGGING
#define LOG_MESSAGE	logMessage
#else
#define LOG_MESSAGE
#endif // _ENABLE_LOGGING

/////////////////////////////////////////////////////////////////////////////
int getTextWidth(CWnd *pWnd, LPCTSTR str);
void DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart,
						   short yStart, COLORREF cTransparentColor);
void throwException(UINT nID);
void pumpMessages();
#ifdef _ENABLE_LOGGING
void logMessage(LPCTSTR fmt, ...);
#endif // ifdef _ENABLE_LOGGING
/////////////////////////////////////////////////////////////////////////////
#endif // __GLOBALS_H__
#if !defined(AFX_LABELCONTROL_H__E4BD62BE_AFB2_4B45_8824_CD17BC7A4F87__INCLUDED_)
#define AFX_LABELCONTROL_H__E4BD62BE_AFB2_4B45_8824_CD17BC7A4F87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CLabelControl wrapper class

class CLabelControl : public CWnd
{
protected:
    DECLARE_DYNCREATE(CLabelControl)
public:
    CLSID const& GetClsid()
    {
        static CLSID const clsid
            = { 0x978c9e23, 0xd4b0, 0x11ce, { 0xbf, 0x2d, 0x0, 0xaa, 0x0, 0x3f, 0x40, 0xd0 } };
        return clsid;
    }
    virtual BOOL Create(LPCTSTR lpszClassName,
                        LPCTSTR lpszWindowName, DWORD dwStyle,
                        const RECT& rect,
                        CWnd* pParentWnd, UINT nID,
                        CCreateContext* pContext = NULL)
    {
        return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
    }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
                const RECT& rect, CWnd* pParentWnd, UINT nID,
                CFile* pPersist = NULL, BOOL bStorage = FALSE,
                BSTR bstrLicKey = NULL)
    {
        return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
                             pPersist, bStorage, bstrLicKey);
    }

// Attributes
public:

// Operations
public:
    void SetAutoSize(BOOL bNewValue);
    BOOL GetAutoSize();
    void SetBackColor(long nNewValue);
    long GetBackColor();
    void SetBackStyle(long nNewValue);
    long GetBackStyle();
    void SetBorderColor(long nNewValue);
    long GetBorderColor();
    void SetBorderStyle(long nNewValue);
    long GetBorderStyle();
    void SetCaption(LPCTSTR lpszNewValue);
    CString GetCaption();
    void SetEnabled(BOOL bNewValue);
    BOOL GetEnabled();
    void SetRefFont(LPDISPATCH newValue);
    COleFont GetFont();
    void SetForeColor(long nNewValue);
    long GetForeColor();
    void SetMouseIcon(LPDISPATCH newValue);
    void SetRefMouseIcon(LPDISPATCH newValue);
    CPicture GetMouseIcon();
    void SetMousePointer(long nNewValue);
    long GetMousePointer();
    void SetPicture(LPDISPATCH newValue);
    void SetRefPicture(LPDISPATCH newValue);
    CPicture GetPicture();
    void SetPicturePosition(long nNewValue);
    long GetPicturePosition();
    void SetSpecialEffect(long nNewValue);
    long GetSpecialEffect();
    void SetTextAlign(long nNewValue);
    long GetTextAlign();
    void SetWordWrap(BOOL bNewValue);
    BOOL GetWordWrap();
    void SetAccelerator(LPCTSTR lpszNewValue);
    CString GetAccelerator();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELCONTROL_H__E4BD62BE_AFB2_4B45_8824_CD17BC7A4F87__INCLUDED_)

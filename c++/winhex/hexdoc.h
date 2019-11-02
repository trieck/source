// hexdoc.h : interface of the HexDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXDOC_H__B1B4E5FC_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_HEXDOC_H__B1B4E5FC_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef const unsigned char* LPCBYTE;

class HexDoc : public CDocument
{
protected: // create from serialization only
    HexDoc();
    DECLARE_DYNCREATE(HexDoc)

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(HexDoc)
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~HexDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    LPCBYTE GetData() const;
    UINT GetDataSize() const;
    void SetData(UINT offset, BYTE data);
protected:
    void Load(CArchive & ar);
    void Save(CArchive & ar);
    void UpdateHexView();

// Generated message map functions
protected:
    //{{AFX_MSG(HexDoc)
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnUpdateDocumentSize(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    BYTE *m_pdata;
    UINT m_nsize;
};

/////////////////////////////////////////////////////////////////////////////

inline LPCBYTE HexDoc::GetData() const
{
    return m_pdata;
}

inline UINT HexDoc::GetDataSize() const
{
    return m_nsize;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXDOC_H__B1B4E5FC_8F9B_11D3_88CE_000000000000__INCLUDED_)

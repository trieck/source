// hexdoc.h : interface of the HexDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXDOC_H__B1B4E5FC_8F9B_11D3_88CE_000000000000__INCLUDED_)
#define AFX_HEXDOC_H__B1B4E5FC_8F9B_11D3_88CE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using LPCBYTE = const unsigned char*;

class HexDoc : public CDocument
{
protected: // create from serialization only
    HexDoc();
    DECLARE_DYNCREATE(HexDoc)

    // Attributes
    // Operations
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(HexDoc)
    BOOL OnNewDocument() override;
    void Serialize(CArchive& ar) override;
    void DeleteContents() override;
    BOOL OnOpenDocument(LPCTSTR lpszPathName) override;
    BOOL OnSaveDocument(LPCTSTR lpszPathName) override;
    //}}AFX_VIRTUAL

    // Implementation
    ~HexDoc() override;
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif
    LPCBYTE GetData() const;
    UINT GetDataSize() const;
    void SetData(UINT offset, BYTE data);
protected:
    void Load(CArchive& ar);
    void Save(CArchive& ar);
    void UpdateHexView();

    // Generated message map functions
    //{{AFX_MSG(HexDoc)
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnUpdateDocumentSize(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    BYTE* m_pdata;
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

#pragma once


// WinADFView view

class WinADFView : public CListView
{
    DECLARE_DYNCREATE(WinADFView)

protected:
    WinADFView();           // protected constructor used by dynamic creation
    virtual ~WinADFView();

public:
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
    WinADFDoc* GetDocument() const;

protected:
    void AddImages();
    void InsertHeaders();
    Entry *GetSelectedEntry(int *pos = NULL);
    void InsertEntry(const Entry &entry);
    BOOL CopyFile(LPCSTR filename, Entry &entry);

    CImageList m_ImageList;
    HCURSOR m_hCursor, m_hStdCursor;

    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
protected:
    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
    afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnViewasText();
    afx_msg void OnViewasBinary();
    afx_msg void OnUpdateViewAsText(CCmdUI *pCmdUI);
    afx_msg void OnUpdateViewAsBinary(CCmdUI *pCmdUI);
    afx_msg void OnUpdateProperties(CCmdUI *pCmdUI);
    afx_msg void OnProperties();
    afx_msg void OnUpdateEntryOpen(CCmdUI *pCmdUI);
    afx_msg void OnEntryOpen();
    afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEntryExport();
    afx_msg void OnUpdateEntryExport(CCmdUI *pCmdUI);
    afx_msg void OnEntryDelete();
    afx_msg void OnUpdateEntryDelete(CCmdUI *pCmdUI);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  //debug version in WinADFView.cpp
inline WinADFDoc* WinADFView::GetDocument() const
{
    return reinterpret_cast<WinADFDoc*>(m_pDocument);
}
#endif

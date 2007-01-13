// musicView.h : interface of the MusicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICVIEW_H__F7CFDC3B_51AB_11D4_89F0_00E098787497__INCLUDED_)
#define AFX_MUSICVIEW_H__F7CFDC3B_51AB_11D4_89F0_00E098787497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _Record{
	long recordId;
	CString Artist;
	CString Album;
	CString Label;
	int format;
	int year;

	_Record(){
		format = 0; year = 0;
	}
	_Record(const _Record & r) {
		recordId = r.recordId;
		Artist = r.Artist;
		Album = r.Album;
		Label = r.Label;
		format = r.format;
		year = r.year;
	}
	_Record & operator =(const _Record & r) {
		if (&r != this) {
			recordId = r.recordId;
			Artist = r.Artist;
			Album = r.Album;
			Label = r.Label;
			format = r.format;
			year = r.year;
		}
		return *this;
	}
} _Record, *LPRECORD;


class MusicView : public CFormView
{
protected: // create from serialization only
	MusicView();
	DECLARE_DYNCREATE(MusicView)

public:
	//{{AFX_DATA(MusicView)
	enum { IDD = IDD_MUSIC_FORM };
	CListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:
	MusicDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MusicView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MusicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void CreateHeaders();
	BOOL MakeRecord(UINT row, LPRECORD prec);

// Generated message map functions
protected:
	//{{AFX_MSG(MusicView)
	afx_msg void OnFind();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in musicView.cpp
inline MusicDoc* MusicView::GetDocument()
   { return (MusicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICVIEW_H__F7CFDC3B_51AB_11D4_89F0_00E098787497__INCLUDED_)

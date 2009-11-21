// musicView.cpp : implementation of the MusicView class
//

#include "stdafx.h"

#include "music.h"
#include "musicDoc.h"
#include "musicView.h"
#include "AddEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static LPCTSTR columns[] = {
	_T("Artist"),
	_T("Album"),
	_T("Label"),
	_T("Format"),
	_T("Year")
};

/////////////////////////////////////////////////////////////////////////////
// MusicView

IMPLEMENT_DYNCREATE(MusicView, CFormView)

BEGIN_MESSAGE_MAP(MusicView, CFormView)
	//{{AFX_MSG_MAP(MusicView)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicView construction/destruction

MusicView::MusicView()
		: CFormView(MusicView::IDD)
{
	//{{AFX_DATA_INIT(MusicView)
	//}}AFX_DATA_INIT
}

MusicView::~MusicView()
{
}

void MusicView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MusicView)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}

BOOL MusicView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void MusicView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	ListView_SetExtendedListViewStyle(m_List,
	                                  ListView_GetExtendedListViewStyle(m_List) |
	                                  LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CreateHeaders();
}

/////////////////////////////////////////////////////////////////////////////
// MusicView printing

BOOL MusicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void MusicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void MusicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void MusicView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// MusicView diagnostics

#ifdef _DEBUG
void MusicView::AssertValid() const
{
	CFormView::AssertValid();
}

void MusicView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

MusicDoc* MusicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MusicDoc)));
	return (MusicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MusicView message handlers

void MusicView::CreateHeaders()
{
	ASSERT(IsWindow(m_List));
	CRect rc;

	m_List.GetWindowRect(rc);

	size_t cols = sizeof(columns) / sizeof(LPCTSTR);

	for (size_t N = 0; N < cols; N++) {
		m_List.InsertColumn(N, columns[N]);
		m_List.SetColumnWidth(N, rc.Width() / cols);
	}
}
void MusicView::OnFind()
{
	CWaitCursor crsr;
	UpdateData();

	CString artist, album, song;
	GetDlgItemText(IDC_ARTIST, artist);
	GetDlgItemText(IDC_ALBUM, album);
	GetDlgItemText(IDC_SONG, song);

	artist.TrimLeft();	artist.TrimRight();
	album.TrimLeft();	artist.TrimRight();
	song.TrimLeft();	song.TrimRight();

	MusicApp *pApp = (MusicApp*)AfxGetApp();
	CDaoDatabase *pdb = pApp->database();
	ASSERT_VALID(pdb);

	CDaoQueryDef query(pdb);
	CDaoRecordset rs(pdb);

	m_List.DeleteAllItems();

	try {
		// create temporary query definition
		CString param1 = _T(" [Artist Name] TEXT");
		CString param2 = _T(" [Album Name] TEXT");
		CString param3 = _T(" [Song Name] TEXT");

		CString sql;
		if (!artist.IsEmpty() || !album.IsEmpty()) {
			sql += _T("PARAMETERS ");

			if (!artist.IsEmpty()) sql += param1;

			if (!album.IsEmpty()) {
				if (!artist.IsEmpty()) sql += _T(", ");
				sql += param2;
			}

			sql += _T(';');
		}

		sql += _T("SELECT * FROM qryAlbumView");

		if (!artist.IsEmpty()) {
			sql += _T(" WHERE Artists.Name = [Artist Name]");
		}
		if (!album.IsEmpty()) {
			if (!artist.IsEmpty())
				sql += _T(" AND");
			else sql += _T(" WHERE");
			sql += _T(" Title = [Album Name]");
		}

		query.Create(NULL, sql);
		if (!artist.IsEmpty()) query.SetParamValue(_T("[Artist Name]"), artist);
		if (!album.IsEmpty()) query.SetParamValue(_T("[Album Name]"), album);

		// open the recordset from the query definition
		rs.Open(&query, dbOpenSnapshot, dbForwardOnly);

		for (int item = 0; !rs.IsEOF(); item++) {
			COleVariant var;
			CString value;

			rs.GetFieldValue(_T("Artists.Name"), var);
			m_List.InsertItem(item, (LPCSTR)var.pbVal);

			rs.GetFieldValue(_T("RecordId"), var);
			m_List.SetItemData(item, var.intVal);

			rs.GetFieldValue(_T("Title"), var);
			m_List.SetItemText(item, 1, (LPCSTR)var.pbVal);

			rs.GetFieldValue(_T("Labels.Name"), var);
			m_List.SetItemText(item, 2, (LPCSTR)var.pbVal);

			rs.GetFieldValue(_T("Type"), var);
			m_List.SetItemText(item, 3, (LPCSTR)var.pbVal);

			rs.GetFieldValue(_T("Release Year"), var);
			value;
			value.Format(_T("%d"), var.intVal);
			m_List.SetItemText(item, 4, value);

			rs.MoveNext();
		}

	} catch (CDaoException *E) {
		E->ReportError(MB_OK | MB_ICONEXCLAMATION);
		E->Delete();
	}

	if (rs.IsOpen())
		rs.Close();
	if (query.IsOpen())
		query.Close();
}

int MusicView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void MusicView::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;

	int item = m_List.GetNextItem(-1, LVNI_SELECTED);
	if (item == -1)
		return;

	_Record record;
	MakeRecord(item, &record);

	AddEditDlg dlg(AddEditDlg::editMode, &record);
	dlg.DoModal();
}

BOOL MusicView::MakeRecord(UINT row, LPRECORD prec)
{
	if (row > (UINT)m_List.GetItemCount() - 1)
		return FALSE;	// not valid row

	ASSERT(prec != NULL);

	CString str;

	prec->recordId = m_List.GetItemData(row);
	prec->Artist = m_List.GetItemText(row, 0);
	prec->Album = m_List.GetItemText(row, 1);
	prec->Label = m_List.GetItemText(row, 2);

	str = m_List.GetItemText(row, 3);
	//prec->format = FormatToIndex(str);

	str = m_List.GetItemText(row, 4);
	sscanf(str, _T("%d"), &prec->year);

	return TRUE;

}
// TorrentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "TorrentMaker.h"
#include "TorrentDlg.h"
#include "StringTokenizer.h"
#include <shlobj.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace {	// anonymous

typedef struct {
	LPCSTR desc;
	int size;
} PIECESIZE;

static PIECESIZE piece_sizes[] = {
/*	{ "(auto detect)", 0 }, */
	{ "32 kB", 1 << 15 },
	{ "64 kB", 1 << 16 },
	{ "128 kB", 1 << 17 },
	{ "256 kB", 1 << 18 },
	{ "512 kB", 1 << 19 },
	{ "1024 kB", 1 << 20 },
	{ "2048 kB", 1 << 21 },
	{ "4096 kB", 1 << 22 }
};

CStringVec ParseTrackers(const CString &input);

}	// anonymous

/////////////////////////////////////////////////////////////////////////////
// TorrentDlg dialog


TorrentDlg::TorrentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TorrentDlg::IDD, pParent), m_pMaker(NULL)
{
	//{{AFX_DATA_INIT(TorrentDlg)
	m_Trackers = _T("");
	m_Private = FALSE;
	m_Comment = _T("");
	//}}AFX_DATA_INIT
}

TorrentDlg::~TorrentDlg()
{
	if (m_pMaker != NULL) {
		delete m_pMaker;
	}
}

void TorrentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TorrentDlg)
	DDX_Control(pDX, IDOK, m_Create);
	DDX_Control(pDX, IDC_SOURCE, m_SourceFiles);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_PIECESIZE, m_PieceSize);
	DDX_Text(pDX, IDC_TRACKERS, m_Trackers);
	DDX_Check(pDX, IDC_PRIVATE, m_Private);
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TorrentDlg, CDialog)
	//{{AFX_MSG_MAP(TorrentDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TorrentDlg message handlers

void TorrentDlg::OnBrowse() 
{
	BROWSEINFO bi;
	CString displayName, fileName;

	memset(&bi, 0, sizeof(BROWSEINFO));
	bi.hwndOwner = *this;
	bi.pszDisplayName = displayName.GetBuffer(_MAX_PATH);
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	displayName.ReleaseBuffer();

	if (pidl != NULL) {
		BOOL fRtn = SHGetPathFromIDList(pidl, 
			fileName.GetBuffer(_MAX_PATH));
		fileName.ReleaseBuffer();
		if (fRtn) {
			m_SourceFiles.SetWindowText(fileName);
		}
		CoTaskMemFree(pidl);
	}		
}

void TorrentDlg::OnOK() 
{
	if (!UpdateData(TRUE)) {
		TRACE0("UpdateData failed during dialog termination.\n");
		return;
	}

	CString sourceFiles;
	int nLen = m_SourceFiles.GetWindowTextLength() + 1;
	m_SourceFiles.GetWindowText(sourceFiles.GetBuffer(nLen), nLen);
	sourceFiles.ReleaseBuffer();

	sourceFiles.TrimLeft(); sourceFiles.TrimRight();
	if (sourceFiles.GetLength() == 0) {
		AfxMessageBox(IDS_NOPATH);
		return;
	}
	
	if (access(sourceFiles, 0) == -1) {
		CString message;
		message.Format(IDS_FILEDOESNOTEXIST, sourceFiles);
		AfxMessageBox(message);
		return;
	}

	CString root;
	AfxGetRoot(sourceFiles, root);
	if (sourceFiles == root) {
		AfxMessageBox(IDS_ROOTNOTALLOWED);
		return;
	}

	CStringVec trackers = ParseTrackers(m_Trackers);
	if (trackers.size() == 0) {
		int nRtn = AfxMessageBox(IDS_NOTRACKERS, 
			MB_YESNO | MB_ICONQUESTION);
		if (nRtn == IDNO) return;
	}

	m_Comment.TrimLeft(); m_Comment.TrimRight();
	
	int current;
	if ((current = m_PieceSize.GetCurSel()) == -1) {
		AfxMessageBox(IDS_NOPIECESIZE); 
		return;
	}

	DWORD pieceSize = m_PieceSize.GetItemData(current);
	
	// Make the torrent
	m_Create.EnableWindow(FALSE);
	
	try {
		m_pMaker->Make(sourceFiles, trackers, m_Comment, 
			pieceSize, m_Private);
	} catch (CUserException *pException) {
		pException->Delete();
		m_Create.EnableWindow(TRUE);
		m_Progress.SetPos(0);
		return;
	}
	
	if (m_pMaker->DidCancel()) {	// user cancelled
		EndDialog(IDCANCEL);
	} else {
		EndDialog(IDOK);
	}
}

/////////////////////////////////////////////////////////////////////////////
// ICallable methods
void TorrentDlg::Call(DWORD param)
{
	if (!IsWindow(m_Progress)) return;

	if (param != 0) {	// total size in pieces
		m_Progress.SetRange32(0, param);	
		m_Progress.SetStep(1);
	} else {
		m_Progress.StepIt();
	}
}

BOOL TorrentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pMaker = new TorrentMaker(this);

	int nentries = sizeof(piece_sizes) / sizeof(PIECESIZE);
	for (int i = 0; i < nentries; i++) {
		m_PieceSize.AddString(piece_sizes[i].desc);
		m_PieceSize.SetItemData(i, piece_sizes[i].size);
	}

	m_PieceSize.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CFile *TorrentDlg::GetFile()
{
	if (m_pMaker != NULL)
		return m_pMaker->GetFile();
	return NULL;
}

namespace {	// anonymous

CStringVec ParseTrackers(const CString &input)
{
	CStringVec output;

	StringTokenizer tokenizer(input, "\r\n\t ");
	CString tok;
	while ((tok = tokenizer.next()) != "") {
		if (tok.GetLength() < 7) continue;
		if (tok.Mid(0, 7) == "http://") 
			output.push_back(tok);
	}

	return output;
}

}	// anonymous

void TorrentDlg::OnCancel() 
{
	if (m_pMaker != NULL)
		m_pMaker->DoCancel();

	CDialog::OnCancel();
}

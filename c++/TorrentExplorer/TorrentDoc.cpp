// TorrentDoc.cpp : implementation of the TorrentDoc class
//

#include "stdafx.h"
#include "TorrentExplorer.h"
#include "Dictionary.h"
#include "List.h"
#include "TorrentDoc.h"
#include "TorrentParser.h"
#include "TorrentMaker.h"
#include "TorrentDlg.h"
#include "TorrentWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TorrentDoc

IMPLEMENT_DYNCREATE(TorrentDoc, CDocument)

BEGIN_MESSAGE_MAP(TorrentDoc, CDocument)
    //{{AFX_MSG_MAP(TorrentDoc)
    ON_COMMAND(ID_FILE_NEW, OnFileNew)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TorrentDoc construction/destruction

TorrentDoc::TorrentDoc()
    : m_pTorrent(NULL)
{
}

TorrentDoc::~TorrentDoc()
{
}

BOOL TorrentDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// TorrentDoc serialization

void TorrentDoc::Serialize(CArchive& ar)
{
    try {
        if (ar.IsLoading()) {
            m_pTorrent = TorrentParser::Parse(ar);
        } else {
            TorrentWriter::Write(m_pTorrent, ar);
        }
    } catch (CException *pException) {
        pException->ReportError();
        pException->Delete();
    }
}

/////////////////////////////////////////////////////////////////////////////
// TorrentDoc diagnostics

#ifdef _DEBUG
void TorrentDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void TorrentDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// TorrentDoc commands

void TorrentDoc::DeleteContents()
{
    if (m_pTorrent != NULL) {
        delete m_pTorrent;
        m_pTorrent = NULL;
    }
    CDocument::DeleteContents();
}

void TorrentDoc::OnFileNew()
{
    TorrentDlg dlg;
    if (dlg.DoModal() == IDOK) {
        AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, 0, 0);
        CArchive ar(dlg.GetFile(), CArchive::load);
        Serialize(ar);
        SetModifiedFlag(TRUE);
        UpdateAllViews(NULL);
    }
}

void TorrentDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}

void TorrentDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}


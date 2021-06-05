// DrumSequencerDoc.cpp : implementation of the CDrumSequencerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrumSequencer.h"
#endif

#include "DrumSequencerDoc.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrumSequencerDoc

IMPLEMENT_DYNCREATE(CDrumSequencerDoc, CDocument)

BOOL CDrumSequencerDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    theApp.Stop();

    m_sequence.Clear();

    return TRUE;
}

// CDrumSequencerDoc serialization

void CDrumSequencerDoc::Serialize(CArchive& ar)
{
    m_sequence.Serialize(ar);
}

// CDrumSequencerDoc diagnostics

#ifdef _DEBUG
void CDrumSequencerDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CDrumSequencerDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrumSequencerDoc commands

void CDrumSequencerDoc::ToggleSub(const CPoint& pt)
{
    m_sequence.ToggleSub(pt);
    SetModifiedFlag();
    UpdateAllViews(nullptr, MAKELONG(pt.x, pt.y), &m_sequence);
}

void CDrumSequencerDoc::DeleteContents()
{
    m_sequence.Clear();

    UpdateAllViews(nullptr);
}

BEGIN_MESSAGE_MAP(CDrumSequencerDoc, CDocument)
        ON_COMMAND(ID_SEQUENCER_PLAY, &CDrumSequencerDoc::OnSequencerPlay)
        ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CDrumSequencerDoc::OnUpdateFileSave)
END_MESSAGE_MAP()

void CDrumSequencerDoc::OnSequencerPlay()
{
    theApp.Play(m_sequence);
}

void CDrumSequencerDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}

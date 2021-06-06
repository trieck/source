// DrumSequencerDoc.cpp : implementation of the CDrumSequencerDoc class
//

#include "stdafx.h"
#include "DrumSequencer.h"
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
        ON_COMMAND(ID_TOGGLE_PLAY, &CDrumSequencerDoc::OnTogglePlay)
END_MESSAGE_MAP()

void CDrumSequencerDoc::OnSequencerPlay()
{
    theApp.Play(m_sequence);
}

void CDrumSequencerDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}

void CDrumSequencerDoc::OnTogglePlay()
{
    if (theApp.IsPlaying()) {
        theApp.Stop();
    } else {
        theApp.Play(m_sequence);
    }
}

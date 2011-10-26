// ScoreDoc.cpp : implementation file
//

#include "stdafx.h"
#include "baseinc.h"
#include "score.h"
#include "ScoreDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MARKER_SIZE 3

// score file marker
static const BYTE scoreMarker[MARKER_SIZE] = {
	0x73,
	0x63,
	0x72
}; // scr

/////////////////////////////////////////////////////////////////////////////
// ScoreDoc

IMPLEMENT_DYNCREATE(ScoreDoc, CDocument)

ScoreDoc::ScoreDoc()
{
}

BOOL ScoreDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

ScoreDoc::~ScoreDoc()
{
}


BEGIN_MESSAGE_MAP(ScoreDoc, CDocument)
	//{{AFX_MSG_MAP(ScoreDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScoreDoc diagnostics

#ifdef _DEBUG
void ScoreDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void ScoreDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ScoreDoc serialization

void ScoreDoc::Serialize(CArchive& ar)
{
	BYTE buffer[MARKER_SIZE];

	if (ar.IsStoring()) {
		ar << scoreMarker[0];   // 's'
		ar << scoreMarker[1];   // 'c'
		ar << scoreMarker[2];   // 'r'
	} else {
		// Is this a valid score archive
		ar.Read(buffer, MARKER_SIZE);
		if (memcmp(buffer, scoreMarker, MARKER_SIZE) != 0)
			AfxThrowArchiveException(CArchiveException::badIndex);
	}

	m_Staff.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// ScoreDoc commands

//
// DeselectAllMeasures
//
void ScoreDoc::DeselectAllMeasures()
{
	m_Staff.DeselectAllMeasures();

	UpdateAllViews(NULL);
}

//
// SelectMeasure
//
void ScoreDoc::SelectMeasure(Measure * pMeasure)
{
	DeselectAllMeasures();

	if (pMeasure != NULL)
		pMeasure->Select(TRUE);

	UpdateAllViews(NULL, measureHint, pMeasure);
}

//
// AddNote
//
BOOL ScoreDoc::AddNote(Measure * pMeasure, Note * pNote)
{
	ASSERT_VALID(pMeasure);
	ASSERT_VALID(pNote);

	if (!pMeasure->AddNote(pNote))
		return FALSE;

	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);

	return TRUE;
}

//
// RemoveNote
//
BOOL ScoreDoc::RemoveNote(Measure * pMeasure, Note * pNote)
{
	ASSERT_VALID(pMeasure);
	ASSERT_VALID(pNote);

	if (!pMeasure->RemoveNote(pNote))
		return FALSE;

	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);

	return TRUE;
}

//
// ModifyNote
//
BOOL ScoreDoc::ModifyNote(Measure * pMeasure, Note * pNote, const Tool & tool)
{
	ASSERT_VALID(pMeasure);
	ASSERT_VALID(pNote);
	ASSERT(tool.type == ModifierTool);

	// Don't allow no op modifiers
	const KeySignature & ks = pMeasure->GetKeySignature();
	Modifier mod = ks.getmodifier(pNote->GetName());

	if (mod == tool.user)
		return FALSE;

	pNote->SetModifier(&tool);
	Note * pForward = pMeasure->ResetForward(pNote);

	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL, modifierHint, pNote);

	if (pForward != NULL)
		UpdateAllViews(NULL, modifierHint, pForward);

	return TRUE;
}

//
// OnDeleteContents
//
void ScoreDoc::DeleteContents()
{
	m_Staff.Clear();

	CDocument::DeleteContents();
}

//
// OnUpdateFileSave
//
void ScoreDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	ASSERT(pCmdUI != NULL);

	pCmdUI->Enable(IsModified());
}


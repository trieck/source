
// DrumSequencerDoc.h : interface of the CDrumSequencerDoc class
//

#pragma once

#include "Sequence.h"

class CDrumSequencerDoc : public CDocument
{
protected: // create from serialization only
    CDrumSequencerDoc();
    DECLARE_DYNCREATE(CDrumSequencerDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
    virtual ~CDrumSequencerDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    Sequence *GetSequence()
    {
        return &m_sequence;
    }
protected:

// Generated message map functions
protected:

#ifdef SHARED_HANDLERS
    // Helper function that sets search content for a Search Handler
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
    void ToggleSub(const CPoint& pt);
private:
    Sequence m_sequence;
public:
    virtual void DeleteContents();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnSequencerPlay();
    afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
};

#pragma once

#include "Sequence.h"

class CDrumSequencerDoc : public CDocument
{
protected: // create from serialization only
    CDrumSequencerDoc() = default;
DECLARE_DYNCREATE(CDrumSequencerDoc)
    BOOL OnNewDocument() override;
    void Serialize(CArchive& ar) override;

    virtual ~CDrumSequencerDoc() = default;
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif
    Sequence* GetSequence()
    {
        return &m_sequence;
    }

    void ToggleSub(const CPoint& pt);

private:
    Sequence m_sequence;
public:
    void DeleteContents() override;
DECLARE_MESSAGE_MAP()
    afx_msg void OnSequencerPlay();
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    afx_msg void OnTogglePlay();
};

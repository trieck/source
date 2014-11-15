/////////////////////////////////////////////////////////////////////////////
//
//	KEYSIG.H : defines a key signature
//
//	Copyright(c) 1999-2011 Thomas A. Rieck, All Rights Reserved
//

#ifndef __KEYSIG_H__
#define __KEYSIG_H__

#include "keynotes.h"

/////////////////////////////////////////////////////////////////////////////
class KeySignature : protected tagKeySignature {
public:
// Construction / Destruction
    KeySignature(int index);
    ~KeySignature();

// Interface
    BOOL ismodifier(const KeyNote *) const;
    Modifier getmodifier(char keyname) const;
    int GetIndex() const {
        return m_index;
    }
    void assign(int index);
    void Render(CDC * pDC, int cx, int cy) const;
    CSize GetSize() const;
protected:
// Implementation
    void SetBitmap();

    int m_index;		// index of key signatures array
    CBitmap * m_pbm;	// key signature bitmap
};
/////////////////////////////////////////////////////////////////////////////

#endif // __KEYSIG_H__
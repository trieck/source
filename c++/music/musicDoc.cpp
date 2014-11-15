// musicDoc.cpp : implementation of the MusicDoc class

//



#include "stdafx.h"

#include "music.h"



#include "musicDoc.h"



#ifdef _DEBUG

#define new DEBUG_NEW

#undef THIS_FILE

static char THIS_FILE[] = __FILE__;

#endif



/////////////////////////////////////////////////////////////////////////////

// MusicDoc



IMPLEMENT_DYNCREATE(MusicDoc, CDocument)



BEGIN_MESSAGE_MAP(MusicDoc, CDocument)

    //{{AFX_MSG_MAP(MusicDoc)

    //}}AFX_MSG_MAP

END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////

// MusicDoc construction/destruction



MusicDoc::MusicDoc()

{

}



MusicDoc::~MusicDoc()

{

}



BOOL MusicDoc::OnNewDocument()

{

    if (!CDocument::OnNewDocument())

        return FALSE;



    return TRUE;

}







/////////////////////////////////////////////////////////////////////////////

// MusicDoc serialization



void MusicDoc::Serialize(CArchive& ar)

{

    if (ar.IsStoring())

    {

    }

    else

    {

    }

}



/////////////////////////////////////////////////////////////////////////////

// MusicDoc diagnostics



#ifdef _DEBUG

void MusicDoc::AssertValid() const

{

    CDocument::AssertValid();

}



void MusicDoc::Dump(CDumpContext& dc) const

{

    CDocument::Dump(dc);

}

#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////

// MusicDoc commands


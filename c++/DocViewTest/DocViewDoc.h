//////////////////////////////////////
// Module Name	:	DocViewDoc.h	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////


#ifndef __DOCVIEWDOC_H__
#define __DOCVIEWDOC_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CDocViewDoc document class

class CDocViewDoc : public CDocument {
protected:
    DECLARE_DYNCREATE(CDocViewDoc)

public:
    CDocViewDoc();
    virtual ~CDocViewDoc();

    // Overrides
    virtual BOOL OnNewDocument();
};

///////////////////////////////////////////////////////////////////

#endif	// __DOCVIEWDOC_H__

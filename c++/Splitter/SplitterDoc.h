///////////////////////////////////////
// Module Name	:	SplitterDoc.h	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////


#ifndef __SPLITTERDOC_H__
#define __SPLITTERDOC_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CSplitterDoc document class

class CSplitterDoc : public CDocument
{
protected:
    DECLARE_DYNCREATE(CSplitterDoc)

public:
    CSplitterDoc();
    virtual ~CSplitterDoc();

    // Overrides
    virtual BOOL OnNewDocument();
};

///////////////////////////////////////////////////////////////////

#endif	// __SPLITTERDOC_H__

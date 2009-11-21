//////////////////////////////////////
// Module Name	:	DocViewApp.h	//
// Author		:	Thomas A. Rieck //
// Purpose		:	Simple Document //
//					 - View Test	//
// Date			:	4/11/97			//
//////////////////////////////////////

#ifndef __DOCVIEWAPP_H__
#define __DOCVIEWAPP_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CDocViewApp application class

class CDocViewApp : public CWinApp {
public:
	CDocViewApp();
	virtual ~CDocViewApp();

	// Overrides
	virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __DOCVIEWAPP_H__

///////////////////////////////////////
// Module Name	:	SplitterApp.h	 //
// Author		:	Thomas A. Rieck  //
// Purpose		:	Splitter Example //
// Date			:	4/11/97			 //
///////////////////////////////////////

#ifndef __SPLITTERAPP_H__
#define __SPLITTERAPP_H__

#include "stdafx.h"

///////////////////////////////////////////////////////////////////
// The CSplitterApp application class

class CSplitterApp : public CWinApp {
public:
	CSplitterApp();
	virtual ~CSplitterApp();

	// Overrides
	virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SPLITTERAPP_H__

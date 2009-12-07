/////////////////////////////////////////////////////////////////////////////
//
// QUITCMD.H: Monitor quit command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __QUITCMD_H__
#define __QUITCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class QuitCmd : public Command
{
public:
	QuitCmd(Monitor *mon);
	~QuitCmd();

	virtual void exec(const stringvec &v); 
};

#endif // __QUITCMD_H__

/////////////////////////////////////////////////////////////////////////////
//
// LOADCMD.H : Monitor load command
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __LOADCMD_H__
#define __LOADCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class LoadCmd : public Command {
public:
	LoadCmd(Monitor *mon);
	~LoadCmd();

	virtual void exec(const stringvec &v);
};

#endif // __LOADCMD_H__


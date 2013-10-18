/////////////////////////////////////////////////////////////////////////////
//
// SAVECMD.H : Monitor save command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __SAVECMD_H__
#define __SAVECMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class SaveCmd : public Command {
public:
	SaveCmd(Monitor *mon);
	~SaveCmd();

	virtual void exec(const stringvec &v);
};

#endif // __SAVECMD_H__


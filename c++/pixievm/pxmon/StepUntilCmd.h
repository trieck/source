/////////////////////////////////////////////////////////////////////////////
//
// STEPUNTILCMD.H : Step until return command
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STEPUNTILCMD_H__
#define __STEPUNTILCMD_H__

#include "Monitor.h"

/////////////////////////////////////////////////////////////////////////////
class StepUntilCmd : public Command, public TrapHandler {
public:
	StepUntilCmd(Monitor *mon);
	~StepUntilCmd();

	virtual void exec(const stringvec &v);
	virtual void trap(void *data);
};

#endif // __STEPUNTILCMD_H__

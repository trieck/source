/////////////////////////////////////////////////////////////////////////////
//
// STEPCMD.H : Monitor step command
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __STEPCMD_H__
#define __STEPCMD_H__

#include "monitor.h"

class StepCmd : public Command {
public:
	StepCmd(Monitor *mon);
	~StepCmd();

	virtual void exec(const stringvec &v);

private:
};

#endif // __STEPCMD_H__
/////////////////////////////////////////////////////////////////////////////
//
// ASSEMCMD.H : Monitor assembler command
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#ifndef __ASSEMCMD_H__
#define __ASSEMCMD_H__

#include "monitor.h"
#include "MiniAssembler.h"

class AssemCmd : public Command {
public:
	AssemCmd(Monitor *mon);
	~AssemCmd();

	virtual void exec(const stringvec &v);
private:
	MiniAssembler assembler;
};

#endif // __ASSEMCMD_H__

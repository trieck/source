/////////////////////////////////////////////////////////////////////////////
//
// DUMPCMD.H : Monitor dump command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __DUMPCMD_H__
#define __DUMPCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class DumpCmd : public Command
{
public:
	DumpCmd(Monitor *mon);
	~DumpCmd();

	virtual void exec(const stringvec &v);
private:
	enum { NBYTES = 16 };	// default number of bytes to dump
};

#endif // __DUMPCMD_H__

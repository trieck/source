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
	enum { LINESIZE = 16 };	// number of bytes per line to dump
	enum { DEFLINES = 9 };	// default number of lines
};

#endif // __DUMPCMD_H__

/////////////////////////////////////////////////////////////////////////////
//
// REGISTERSCMD.H : Monitor registers command
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __REGISTERSCMD_H__
#define __REGISTERSCMD_H__

#include "monitor.h"

/////////////////////////////////////////////////////////////////////////////
class RegistersCmd : public Command {
public:
	RegistersCmd(Monitor *mon);
	~RegistersCmd();

	void exec(const stringvec &v);

};

#endif // __REGISTERSCMD_H__

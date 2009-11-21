/////////////////////////////////////////////////////////////////////////////
//
//	PROCKILL.H : NT process killer
//

#ifndef __PROCKILL_H__
#define __PROCKILL_H__

#include "procenum.h"

/////////////////////////////////////////////////////////////////////////////
class ProcessKiller {
// Construction / Destruction
public:
	ProcessKiller();
	virtual ~ProcessKiller();

// Interface
	void kill(const PidVector &pids, ostream *pstream = NULL);

// Implementation
protected:
	void kill(DWORD pid, ostream *pstream = NULL);
	bool enablePrivileges();
private:
	HANDLE hToken;
};
/////////////////////////////////////////////////////////////////////////////

#endif __PROCKILL_H__
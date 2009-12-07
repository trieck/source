/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.H : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "Trap.h"
#include "Handler.h"
#include "RefObj.h"

// Forward declarations
class Monitor;

/////////////////////////////////////////////////////////////////////////////
// Monitor command
class Command {
public:
	Command(Monitor *pmon) : mon(pmon) {}
	virtual ~Command() {}

	virtual void exec(const stringvec &v) = 0;

protected:
	Monitor *getMonitor() {
		return mon;
	}
private:
	Monitor *mon;	/* back pointer to the monitor */
};
/////////////////////////////////////////////////////////////////////////////

typedef Command *LPCOMMAND;
typedef map<string, LPCOMMAND, stringless> CommandMap;

/////////////////////////////////////////////////////////////////////////////
// Monitor class
class Monitor : public TrapHandler, public Handler {
// Construction / Destruction
public:
	Monitor();
	virtual ~Monitor();

// Interface
	virtual void trap(void *data);
	virtual void handle();

	void setExit(bool f);
	void disassemble(word address);

// Implementation
private:
	void run();
	void runLoop(void *data);

	void dispatch(const string &line);
	void prompt() const;
	void notice() const;

	CommandMap commands;	/* map of commands */
	bool exit_mon;			/* exit flag */
	bool show_notice;		/* show notice */
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline void Monitor::setExit(bool f)
{
	exit_mon = f;
}

#endif // __MONITOR_H__

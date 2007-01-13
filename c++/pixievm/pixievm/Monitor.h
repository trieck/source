/////////////////////////////////////////////////////////////////////////////
//
// MONITOR.H : Pixie Virtual Machine Monitor
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MONITOR_H__
#define __MONITOR_H__

// Forward declarations
class Monitor;

/////////////////////////////////////////////////////////////////////////////
// Monitor command
class Command 
{
public:
	Command(Monitor *pmon) : mon(pmon) {}
	virtual ~Command() {}

	virtual void exec(const stringvec &v) = 0;

protected:
	Monitor *getMonitor() { return mon; }
private:
	Monitor *mon;	/* back pointer to the monitor */
};
/////////////////////////////////////////////////////////////////////////////

typedef Command *LPCOMMAND;
typedef map<string, LPCOMMAND, stringless> CommandMap;

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Monitor class
class Monitor : public TrapHandler 
{
// Construction / Destruction
public:
	Monitor();
	virtual ~Monitor();

// Interface
	
	void trap(void *data);
	void setExit(bool f);

// Implementation
private:
	void run(void *data);
	void dispatch(const string &line);
	void prompt();
	void notice();

	CommandMap commands;	/* map of commands */
	bool exit_mon;			/* exit flag */
	bool show_notice;		/* show notice */
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline void Monitor::setExit(bool f) {
	exit_mon = f;
}

#endif // __MONITOR_H__

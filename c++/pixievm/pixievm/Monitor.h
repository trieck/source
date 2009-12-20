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
class Command : public RefObj {
protected:
	Command(Monitor *pmon) : m_mon(pmon), m_ref(1) {}
public:
	virtual ~Command() {}

	Command *CopyRef() {
		IncRef();
		return this;
	}

	virtual void exec(const stringvec &v) = 0;

	uint32_t IncRef() {
		return ++m_ref;
	}
	uint32_t DecRef() {
		if (--m_ref == 0) {
			delete this;
			return 0;
		}
		return m_ref;
	}
protected:
	Monitor *getMonitor() {
		return m_mon;
	}
private:
	Monitor *m_mon;	// back pointer to the monitor
	uint32_t m_ref;	// reference count on the object
};
/////////////////////////////////////////////////////////////////////////////

typedef Command *LPCOMMAND;
typedef map<string, LPCOMMAND, stringless> CommandMap;

class Monitor;
typedef auto_ptr<Monitor> MonitorPtr;

/////////////////////////////////////////////////////////////////////////////
// Monitor class
class Monitor : public TrapHandler, public Handler {
// Construction / Destruction
private:
	Monitor();
public:
	virtual ~Monitor();

// Interface
	static Monitor *getInstance();

	virtual void trap(void *data);
	virtual void handle();
	
	void setExit(bool f);
	void disassemble(word address);
	bool isRunning() const { return !m_exit_mon; }

// Implementation
private:
	void run();
	void runLoop(void *data);

	void dispatch(const string &line);
	void prompt() const;
	void notice() const;

	static void sighandler(int signal);

	CommandMap m_commands;			// map of commands 
	bool m_exit_mon;				// exit flag 
	bool m_show_notice;				// show notice 
	static MonitorPtr instance;		// singleton instance
};
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
inline void Monitor::setExit(bool f) {
	m_exit_mon = f;
}

#endif // __MONITOR_H__

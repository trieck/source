/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.H : Implementation of interrupts
//
// Copyright (c) 2006-2009, Thomas A. Rieck, All Rights Reserved
//

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/////////////////////////////////////////////////////////////////////////////
// Types of interrupt lines
enum cpu_int {
	IK_NONE		= 0,
	IK_NMI		= 1 << 0,
	IK_IRQ		= 1 << 1,
	IK_RESET	= 1 << 2,
	IK_TRAP		= 1 << 3,
	IK_MONITOR	= 1 << 4
};

/////////////////////////////////////////////////////////////////////////////
class Interrupt {
public:
	Interrupt();
	virtual ~Interrupt();

	int getPending() const {
		return m_pending;
	}
	void setPending(int p) {
		m_pending |= p;
	}
	void clearPending(int p) {
		m_pending &= ~p;
	}

	void setTrap(LPTRAPHANDLER handler, void *data);
	void handleTrap();

	void setMonitor(LPHANDLER handler);
	void handleMonitor();

private:
	// pending interrupt
	int m_pending;

	// trap handler
	LPTRAPHANDLER m_trapHandler;
	
	// monitor handler
	LPHANDLER m_monHandler;

	// trap data 
	void *m_trapData;
};

// global interrupt declaration
extern Interrupt g_interrupt;

/////////////////////////////////////////////////////////////////////////////
#endif // __INTERRUPT_H__

/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.H : Implementation of interrupts
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
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
class interrupt_st {
public:
	interrupt_st();
	virtual ~interrupt_st();

	int getPending() const {
		return pending;
	}
	void setPending(int p) {
		pending |= p;
	}
	void clearPending(int p) {
		pending &= ~p;
	}
	void setTrap(LPTRAPHANDLER handler, void *data);

	void handleTrap();

private:
	/* pending interrupt */
	int pending;

	/* trap handler */
	LPTRAPHANDLER trap;

	/* trap data */
	void *trap_data;
};

extern interrupt_st g_interrupt;

/////////////////////////////////////////////////////////////////////////////
#endif // __INTERRUPT_H__

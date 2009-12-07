/////////////////////////////////////////////////////////////////////////////
//
// INTERRUPT.CPP : Implementation of interrupts
//
// Copyright (c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "Trap.h"
#include "Handler.h"
#include "Interrupt.h"

// global interrupt
Interrupt g_interrupt;

/////////////////////////////////////////////////////////////////////////////
Interrupt::Interrupt()
{
	memset(this, 0, sizeof(Interrupt));
}

/////////////////////////////////////////////////////////////////////////////
Interrupt::~Interrupt()
{
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::handleTrap()
{
	if (m_trapHandler != NULL) {
		m_trapHandler->trap(m_trapData);
	}
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::setTrap(LPTRAPHANDLER handler, void *data)
{
	m_pending |= IK_TRAP;
	m_trapHandler = handler;
	m_trapData = data;
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::setMonitor(LPHANDLER handler)
{
	m_pending |= IK_MONITOR;
	m_monHandler = handler;
}

/////////////////////////////////////////////////////////////////////////////
void Interrupt::handleMonitor()
{
	if (m_monHandler != NULL) {
		m_monHandler->handle();
	}
}


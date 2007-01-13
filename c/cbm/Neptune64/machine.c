/*
 * 	MACHINE.C
 *
 * 	Machine definitions
 *
 *	Neptune64 Commodore 64 Emulator
 * 	Copyright (C) 2001 Thomas A. Rieck <trieck@bellsouth.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 */
#include "common.h"
#include "6510.h"
#include "machine.h"
#include "mem.h"
#include "disassem.h"
#include "video.h"
#include "opcodes.h"
#include "cia.h"
int err = 0;	/* indicates an error during execution */ 
/* 
 * initialize machine
 */
void machine_init(void) 
{
	/* FIXME: is order significant */
	mem_init();
	cia_init();
	vic_init();
}
/*
 * step the machine
 */
void machine_step(const word *addr)
{
	byte i;
	const Instr *pi;
		
	if (NULL != addr)
		cpu.pc = *addr;
	/* disassemble the instruction */
	disassemble_instr(cpu.pc);
	/* fetch the instruction */
	i = fetch_byte(cpu.pc);
		
	pi = instructions[i];
	if (NULL == pi) {
		warning("unrecognized instruction \"$%.2x\" at $%.4hx.\n", 
		i, cpu.pc);
		return;
	}
	
	/* execute the instruction */
	(*pi->fnc)();
}
void machine_go(const word addr)
{
	/* FIXME: this used to work */
}

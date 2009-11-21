/*
 *	CIA.C
 *
 *	complex interface adapter definitions
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
#include "cia.h"
typedef struct {
	byte pra;		/* data register a */
	byte prb;		/* data register b */
	byte ddra;		/* data direction register a */
	byte ddrb;		/* data direction register b */
	byte talo;		/* timer a low byte */
	byte tahi;		/* timer a high byte */
	byte tblo;		/* timer b low byte */
	byte tbhi;		/* timer b high byte */
	byte tod_tenth;	/* time of day clock */
	byte tod_sec;
	byte tod_min;
	byte tod_hr;
	byte sdr;		/* serial data register */
	byte icr;		/* interrupt control register */
	byte cra;		/* control register a */
	byte crb;		/* control register b */
} CIA;
static CIA cia1, cia2;
/*
 * initialize CIA's
 */
void cia_init(void)
{
	memset(&cia1, 0, sizeof(CIA));
	memset(&cia2, 0, sizeof(CIA));
}
/*
 * read a byte from cia1
 */
byte cia1_read(word address)
{
	return 0;
}
/*
 * store a byte at cia1
 */
void cia1_store(word address, byte value)
{
}
/*
 * read a byte from cia2
 */
byte cia2_read(word address)
{
	return 0;
}
/*
 * store a byte at cia2
 */
void cia2_store(word address, byte value)
{
}

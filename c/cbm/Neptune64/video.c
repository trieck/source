/*
 * 	VIDEO.C
 *
 * 	video routines
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
#include "video.h"
#include "mem.h"
#define REGISTERS 	0x2f
static byte memory[REGISTERS];
/* initialize video */
void vic_init(void)
{
	memset(memory, 0, sizeof(memory));
}
/*
 * read byte from vic
 */
byte vic_read(word address)
{
	address &= 0x3f;

	if (address == 0x1e || address == 0x1f)
		return (memory[address] = 0);

	if (address >= 0x2f && address <= 0x3f)
		return 0xff;

	return memory[address];
}
/*
 * store byte
 */
void vic_store(word address, byte b)
{
}
/*
 * read byte from colorram
 */
byte colorram_read(word address)
{
	return 0;
}
/*
 * store colorram byte
 */
void colorram_store(word address, byte b)
{
}

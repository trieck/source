/*
 *	CART.C
 *
 *	cartridge definitions
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
#include "cart.h"
export_t export;
byte read_roml(word addr)
{
    /* FIXME: implement this */
    return 0;
}
byte read_romh(word addr)
{
	/* FIXME: implement this */
	return 0;
}
void store_roml(word addr, byte value)
{
	/* FIXME: implement this */
}
byte read_ultimax_a000_bfff(word addr)
{
	/* FIXME: implement this */
	return 0;
}
void store_ultimax_a000_bfff(word addr, byte value)
{
	/* FIXME : implement this */
}

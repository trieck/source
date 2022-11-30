/*
 *	CART.H
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
#ifndef __CART_H__
#define __CART_H__

/* expansion port signals */
typedef struct
{
    byte exrom;
    byte game;
} export_t;

extern export_t export;

/***************************************************************************/
byte read_roml(word addr);
void store_roml(word addr, byte value);
byte read_romh(word addr);
byte read_ultimax_a000_bfff(word addr);
void store_ultimax_a000_bfff(word addr, byte value);
/***************************************************************************/

#endif /* __CART_H__ */

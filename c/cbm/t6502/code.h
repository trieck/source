/*
 * 	CODE.H	code generation
 *
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
#ifndef __CODE_H__
#define __CODE_H__

#include "opcodes.h"

/***************************************************************************/
void code(addrmode mode, byte);
void resolve(void);
void set_base(word base);
void write_byte(byte);
void write_code(void);
word getmem(void);
byte get_byte(int offset);
/***************************************************************************/

#endif							/* __CODE_H__ */

/*
 * 	COMMON.H
 *
 * 	Common include file
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
 *
 */
#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log.h"
#include "util.h"

typedef unsigned short word;
typedef unsigned char byte;

#define lobyte(w) ((byte)(w))
#define hibyte(w) ((byte)(((word)(w) >> 8) & 0xff))

/* addressing modes */
typedef enum
{
    acc,
    /* accumulator */
    imm,
    /* immediate */
    zpg,
    /* zero page */
    zpx,
    /* zero page, x */
    zpy,
    /* zero page, y */
    absl,
    /* absolute */
    abx,
    /* absolute, x */
    aby,
    /* absolute, y */
    imp,
    /* implied */
    rel,
    /* relative */
    idx,
    /* indirect x */
    idy,
    /* indirect y */
    ind /* indirect */
} addrmode;

#endif /* __COMMON_H__ */

/*
 * 	FIXUP.H	: fixups table
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

#pragma once
#include "common.h"

typedef enum
{
    FIXUP_REG = 0,
    /* regular old fixup */
    FIXUP_BRANCH,
    /* relative branch fix up */
    FIXUP_LO,
    /* lo-byte address fixup */
    FIXUP_HI,
    /* hi-byte address fixup */
} fixup_type;

typedef struct fixup
{
    char* name;         /* fixup name */
    word mem;           /* memory location */
    struct fixup* next; /* next symbol to resolve in list */
    fixup_type type;    /* fixup type */
    int lineno;         /* line number where fixup was generated */
} fixup;

typedef fixup* FixupTable;

/***************************************************************************/
void fixupfree(FixupTable);
fixup* fixupinsert(FixupTable* table, const char* name, word mem,
                   fixup_type type);
/***************************************************************************/

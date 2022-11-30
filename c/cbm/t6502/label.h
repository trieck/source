/*
 * 	LABEL.H	: labels table
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
#ifndef __LABEL_H__
#define __LABEL_H__

typedef struct label
{
    char* name;         /* label name */
    const byte* mem;    /* memory location encountered */
    struct label* next; /* next symbol to resolve in list */
    int isrel;          /* is this a relative branch fix-up */
} label;

typedef label* LabelTable;

/***************************************************************************/
void labelfree(LabelTable);
label* labelinsert(LabelTable* table, const char* name, const byte* mem,
                   int isrel);
/***************************************************************************/

#endif							/* __LABEL_H__ */

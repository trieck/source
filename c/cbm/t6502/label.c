/*
 * 	LABEL.C : label table
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
#include "common.h"
#include "label.h"
static LabelTable labelalloc(void);
/* 
 * allocate a label
 */
LabelTable labelalloc(void)
{
	label *table = (LabelTable) malloc(sizeof(label));
	memset(table, 0, sizeof(label));
	return table;
}

/*
 * free a label
 */
void labelfree(LabelTable table)
{
	while (table != NULL) {
		label *psave = table->next;
		free(table->name);
		free(table);
		table = psave;
	}
}

/* 
 * insert a label
 */
label *labelinsert(LabelTable * table, const char *name,
				   const byte * mem, int isrel)
{
	/* insert at front of list */
	label *pthis = labelalloc();
	pthis->name = strcopy(name);
	pthis->mem = mem;
	pthis->next = *table;
	pthis->isrel = isrel;
	*table = pthis;
	return pthis;
}

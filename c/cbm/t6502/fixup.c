/*
 * 	FIXUP.C : fixups table
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
#include "fixup.h"

extern int yylineno;

static FixupTable fixupalloc(void);

/*
 * allocate a fixup
 */
FixupTable fixupalloc(void)
{
    fixup* table = malloc(sizeof(fixup));
    memset(table, 0, sizeof(fixup));
    return table;
}

/*
 * free a fixup
 */
void fixupfree(FixupTable table)
{
    while (table != NULL) {
        fixup* psave = table->next;
        free(table->name);
        free(table);
        table = psave;
    }
}

/*
 * insert a fixup
 */
fixup* fixupinsert(FixupTable* table, const char* name,
                   word mem, fixup_type type)
{
    /* insert at front of list */
    fixup* fixup = fixupalloc();
    fixup->name = strcopy(name);
    fixup->mem = mem;
    fixup->type = type;
    fixup->lineno = yylineno;
    fixup->next = *table;
    
    *table = fixup;

    return fixup;
}

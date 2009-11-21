/*
 *	EXTERN.C : external declarations
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
#include "extern.h"
typedef struct _extern {
	char *name;					/* name of external */
	struct _extern *next;		/* next external */
} Extern;
static Extern *externals;		/* external list */
extern int lineno;				/* current line number */
static Extern *extern_alloc(void);
static Extern *extern_lookup(const char *name);

/*
 * initialize externals list
 */
void extern_init(void)
{
	externals = extern_alloc();
}

/*
 * allocate an external
 */
Extern *extern_alloc(void)
{
	Extern *pextern = (Extern *) malloc(sizeof(Extern));
	memset(pextern, 0, sizeof(Extern));
	return pextern;
}

/*
 * free externals list
 */
void extern_free(void)
{
	Extern *pextern = externals;
	while (pextern != NULL) {
		Extern *pnext = pextern->next;

		if (pextern->name != NULL)
			free(pextern->name);

		free(pextern);

		pextern = pnext;
	}
}

/*
 * insert an external declaration
 */
void extern_insert(const char *name)
{
	Extern *pextern = extern_lookup(name);
	if (pextern != NULL) {
		warning("external declaration %s already declared at line %d.\n",
		        name, lineno);
		return;
	}

	/* insert at front of list */
	pextern = extern_alloc();
	pextern->name = strcopy(name);
	pextern->next = externals;
	externals = pextern;
}

/*
 * lookup external by name
 */
Extern *extern_lookup(const char *name)
{
	Extern *pextern = externals;
	while (pextern != NULL) {
		if (pextern->name && strcmp(pextern->name, name) == 0)
			return pextern;

		pextern = pextern->next;
	}

	return NULL;
}

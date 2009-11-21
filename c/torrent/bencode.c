/*
 * BENCODE.C
 *
 * Bencode library
 * Copyright (c) 2006, Thomas A. Rieck
 */

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "bencode.h"
#include "btdict.h"

static void free_bt_list(bt_list *l);

/* free allocated element */
void free_element(bt_element e)
{
	switch (e.type) {
	case ET_STRING:
		free(e.sval->data);
		free(e.sval);
		break;
	case ET_LIST:
		free_bt_list(e.lval);
		break;
	case ET_DICT:
		free_bt_dict(e.dval);
		break;
	}
}

/* free allocated list */
void free_bt_list(bt_list *l)
{
	if (l) {
		bt_list *next = l->next;
		free_element(l->e);
		free(l);
		free_bt_list(next);
	}
}

/* allocate a bt_string */
bt_string *alloc_bt_string(void)
{
	bt_string *s = (bt_string*)malloc(sizeof(bt_string));
	memset(s, 0, sizeof(bt_string));
	return s;
}

/* allocate a bt_list */
bt_list *alloc_bt_list(void)
{
	bt_list *l = (bt_list*)malloc(sizeof(bt_list));
	memset(l, 0, sizeof(bt_list));
	return l;
}


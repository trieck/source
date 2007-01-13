/*
 * BENCODE.H
 *
 * Bencode library
 * Copyright (c) 2006, Thomas A. Rieck
 */

#ifndef __BENCODE_H__
#define __BENCODE_H__

/* element types */
#define ET_UNDEF	0
#define ET_INTEGER	1
#define ET_STRING	2
#define ET_LIST		3
#define ET_DICT		4

/* forward declarations */
struct bt_string;
struct bt_list;
struct bt_dict;

/* bencode element */
typedef struct bt_element {
	int type;
	union {
		__int64 ival;
		struct bt_string *sval;
		struct bt_list *lval;
		struct bt_dict *dval;
	};
} bt_element;

/* string */
typedef struct bt_string {
	int nlen;
	char *data;
} bt_string;

/* list */
typedef struct bt_list {
	bt_element e;
	struct bt_list *next;
} bt_list;

/* free element */
void free_element(bt_element e);

/* allocate a string */
bt_string *alloc_bt_string(void);

/* allocate a list */
bt_list *alloc_bt_list(void);

#endif /* __BENCODE_H__ */

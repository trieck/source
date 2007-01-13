/*
 * BTDICT.H
 *
 * Red-Black tree for use 
 * with bencoded dictionaries
 *
 * Copyright (c) 2006, Thomas A. Rieck
 */

#ifndef __BTDICT_H__
#define __BTDICT_H__

/* dictionary */
typedef struct bt_dict {
	char *key;				/* key of node */
	bt_element *val;		/* value of node */
	int red;				/* coloring */
	struct bt_dict *left;	/* left link */
	struct bt_dict *right;	/* right link */
} bt_dict;

/* allocate a dictionary */
bt_dict *alloc_bt_dict(void);

/* free a dictionary */
void free_bt_dict(bt_dict *d);

/* insert item into dictionary */
void bt_dict_insert(bt_dict *t, const char *k, bt_element *v);

/* search dictionary for key */
bt_element *bt_dict_search(bt_dict *t, const char *k);

/* dictionary helper functions */
bt_string *bt_dict_string(struct bt_dict *d, const char *k);
const char *bt_dict_cstring(struct bt_dict *d, const char *k);
__int64 bt_dict_int(struct bt_dict *d, const char *k);
struct tm *bt_dict_date(struct bt_dict *d, const char *k);
bt_list *bt_dict_list(struct bt_dict *d, const char *k);
struct bt_dict *bt_dict_dict(struct bt_dict *d, const char *k);

#endif /* __BTDICT_H__ */
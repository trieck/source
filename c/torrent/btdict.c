/*
 * BTDICT.C
 *
 * Red-Black tree for use
 * with bencoded dictionaries
 *
 * Copyright (c) 2006, Thomas A. Rieck
 */

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include "bencode.h"
#include "btdict.h"

static bt_dict *mknode(const char *k, bt_element *v);
static void xfernode(bt_dict *t, const char *k, bt_element *v);
static bt_dict *split(bt_dict *head, bt_dict *t, bt_dict *p, bt_dict *g,
                      bt_dict *gg, const char *k);
static bt_dict *rotate(bt_dict *t, const char *k);
static int less(const char *k1, const char *k2);

/* allocate a dictionary */
bt_dict *alloc_bt_dict(void)
{
	bt_dict *d = (bt_dict*)malloc(sizeof(bt_dict));
	memset(d, 0, sizeof(bt_dict));
	return d;
}

/* free a dictionary */
void free_bt_dict(bt_dict *t)
{
	if (t) {
		free(t->key);
		free_element(*t->val);
		free(t->val);
		free_bt_dict(t->left);
		free_bt_dict(t->right);
		free(t);
	}
}

/* insert into red-black tree */
void bt_dict_insert(bt_dict *t, const char *k, bt_element *v)
{
	bt_dict *p, *g, *gg, *x;
	int n;

	if (t->key == NULL) {	/* initially empty tree */
		xfernode(t, k, v);
		return;
	}

	x = p = g = t;
	while (x != NULL) {
		gg = g;
		g = p;
		p = x;
		n = strcmp(k, x->key);
		if (n == 0) return;	/* no dupes */
		x = n < 0 ? x->left : x->right;
		if (x && x->left && x->right && x->left->red && x->right->red)
			x = split(t, x, p, g, gg, k);
	}

	x = mknode(k, v);
	if (less(k, p->key)) p->left = x;
	else p->right = x;
	split(t, x, p, g, gg, k);
}

/* search a red-black tree */
bt_element *bt_dict_search(bt_dict *t, const char *k)
{
	int n;

	if (t == NULL || t->key == NULL)
		return NULL;

	n = strcmp(k, t->key);
	if (n == 0) {
		return t->val;
	} else if (n < 0) {
		return bt_dict_search(t->left, k);
	} else {
		return bt_dict_search(t->right, k);
	}

	/* unreachable */
}

bt_dict *split(bt_dict *head, bt_dict *t, bt_dict *p, bt_dict *g, bt_dict *gg, const char *k)
{
	t->red = 1;
	if (t->left) t->left->red = 0;
	if (t->right) t->right->red = 0;

	if (p->red) {
		g->red = 1;
		if (less(k, g->key) != less(k, p->key)) p = rotate(t, k);
		t = rotate(gg, k);
		t->red = 0;
	}

	head->red = 0;
	return t;
}

bt_dict *rotate(bt_dict *t, const char *k)
{
	bt_dict *c, *gc;
	int m, n;

	m = strcmp(k, t->key);
	c = m < 0 ? t->left : t->right;
	if (c == NULL) gc = NULL;
	else {
		n = strcmp(k, c->key);
		if (n < 0) {
			gc = c->left;
			c->left = gc->right;
			gc->right = c;
		} else {
			gc = c->right;
			c->right = gc->left;
			gc->left = c;
		}
	}

	if (m < 0) t->left = gc;
	else t->right = gc;

	return gc;
}

/* make a new node */
bt_dict *mknode(const char *k, bt_element *v)
{
	bt_dict *t = alloc_bt_dict();
	xfernode(t, k, v);
	return t;
}

/* transfer value onto node */
void xfernode(bt_dict *t, const char *k, bt_element *v)
{
	t->key = (char*)malloc(strlen(k) + 1);
	strcpy(t->key, k);
	t->val = malloc(sizeof(bt_element));
	memcpy(t->val, v, sizeof(bt_element));
}

/* boolean comparison of string keys */
int less(const char *k1, const char *k2)
{
	return strcmp(k1, k2) < 0 ? 1 : 0;
}

/* dictionary helper functions */

/* retrieve a string value from dictionary */
bt_string *bt_dict_string(bt_dict *d, const char *k)
{
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return NULL;
	if (v->type != ET_STRING) return NULL;
	return v->sval;
}

/* retrieve a C-style string value from dictionary */
const char *bt_dict_cstring(bt_dict *d, const char *k)
{
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return NULL;
	if (v->type != ET_STRING) return NULL;
	return v->sval->data;
}

/* retrieve an int value from dictionary */
__int64 bt_dict_int(bt_dict *d, const char *k)
{
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return 0;
	if (v->type != ET_INTEGER) return 0;
	return v->ival;
}

/* retrieve a date value from dictionary */
struct tm *bt_dict_date(bt_dict *d, const char *k) {
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return NULL;
	if (v->type != ET_INTEGER) return 0;
	return localtime((time_t*)&v->ival);
}

/* retrieve a list from dictionary */
bt_list *bt_dict_list(bt_dict *d, const char *k)
{
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return NULL;
	if (v->type != ET_LIST) return NULL;
	return v->lval;
}

/* retrieve a dictionary from dictionary */
bt_dict *bt_dict_dict(bt_dict *d, const char *k)
{
	bt_element *v = bt_dict_search(d, k);
	if (v == NULL) return NULL;
	if (v->type != ET_DICT) return NULL;
	return v->dval;
}

/*
 * LEX.C
 *
 * Lexical analyzer for bencoded files
 * Copyright (c) 2006, Thomas A. Rieck
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include <time.h>

#include "bencode.h"
#include "btdict.h"
#include "lex.h"
#include "ui.h"

static int gettok(FILE *fp);
static int lookahead(FILE *fp);
static bt_element dictionary(FILE *fp);
static bt_element integer(FILE *fp);
static bt_element list(FILE *fp);
static bt_element string(FILE *fp);

/* get next input token from stream */
int gettok(FILE *fp)
{
	int c;
	c = fgetc(fp);

	switch (c) {
	case 'd':
		return ET_DICT;
	case 'i':
		return ET_INTEGER;
	case 'l':
		return ET_LIST;
	default:
		if (isdigit(c)) {
			ungetc(c, fp);
			return ET_STRING;
		}
	}
	return c;
}

/* lookahead one token */
int lookahead(FILE *fp)
{
	int c = fgetc(fp);
	ungetc(c, fp);
	return c;
}

/* load element from stream */
bt_element getelement(FILE *fp)
{
	bt_element e;
	int t;

	memset(&e, 0, sizeof(bt_element));
	t = gettok(fp);

	switch (t) {
	case ET_DICT:
		return dictionary(fp);
	case ET_INTEGER:
		return integer(fp);
	case ET_LIST:
		return list(fp);
	case ET_STRING:
		return string(fp);
	default:
		ui_error("unexpected token 0x%.2x.\n", t);
		break;
	}

	return e;
}

/* load dictionary from stream */
bt_element dictionary(FILE *fp)
{
	bt_element e, k, v;
	int c;

	memset(&e, 0, sizeof(bt_element));
	e.type = ET_DICT;
	e.dval = alloc_bt_dict();

	while ((c = lookahead(fp)) != 'e' && c != EOF) {
		k = string(fp);
		v = getelement(fp);
		bt_dict_insert(e.dval, k.sval->data, &v);
		free_element(k);
	}

	gettok(fp);	/* 'e' */

	return e;
}

/* load integer from stream */
bt_element integer(FILE *fp)
{
	bt_element e;
	memset(&e, 0, sizeof(bt_element));

	e.type = ET_INTEGER;
	fscanf(fp, "%I64de", &e.ival);

	return e;
}

/* load list from stream */
bt_element list(FILE *fp)
{
	bt_element e;
	bt_list *l = NULL;
	int c;

	memset(&e, 0, sizeof(bt_element));
	e.type = ET_LIST;

	while ((c = lookahead(fp)) != 'e' && c != EOF) {
		if (l == NULL) e.lval = l = alloc_bt_list();
		else {
			l->next = alloc_bt_list();
			l = l->next;
		}
		l->e = getelement(fp);
	}

	gettok(fp);	/* 'e' */

	return e;
}

/* load string from stream */
bt_element string(FILE *fp)
{
	bt_element e;
	int c, len = 0;
	char *p;

	e.type = ET_STRING;
	fscanf(fp, "%d:", &len);
	e.sval = alloc_bt_string();
	e.sval->nlen = len;
	e.sval->data = p = (char*)malloc(len + 1);

	while (p - e.sval->data < len) {
		c = fgetc(fp);
		if (c == EOF) break;
		*p++ = c;
	}
	*p = '\0';

	return e;
}

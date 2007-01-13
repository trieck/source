/*
 * LIST.H
 *
 * Doubly-linked list
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */

#ifndef __LIST_H__
#define __LIST_H__

/* node in the list */
typedef struct ListNode {
	PSYMBOL sym;
	struct ListNode *prev, *next;
} ListNode, *PLISTNODE;

/* linked list structure */
typedef struct LinkedList {
	unsigned size;
	PLISTNODE head, tail;
} LinkedList, *PLIST;

PLIST listalloc(void);
PLIST listcopy(PLIST src);
void listadd_head(PLIST list, PSYMBOL sym);
void listadd_tail(PLIST list, PSYMBOL sym);
void listfree(PLIST);

#endif							/* __LIST_H__ */

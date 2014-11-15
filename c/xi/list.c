/*
 * LIST.C
 *
 * Doubly-linked list
 *
 * 'X' Programming Language
 * Copyright(c) 2004, Thomas A. Rieck
 * All Rights Reserved
 *
 */
#include <stdlib.h>
#include "symbol.h"
#include "list.h"
#include "xmalloc.h"
#include "x.h"

static PLISTNODE mknode(PSYMBOL);

/* allocate a new list */
PLIST listalloc(void)
{
    PLIST list = (PLIST) xmalloc(sizeof(LinkedList));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}

/* add item to head of list */
void listadd_head(PLIST list, PSYMBOL sym)
{
    PLISTNODE next = list->head;
    list->head = mknode(sym);
    list->head->next = next;
    if (next) {
        next->prev = list->head;
    } else {					/* no previous tail */
        list->tail = list->head;
    }

    list->size++;
}

/* add item to tail of list */
void listadd_tail(PLIST list, PSYMBOL sym)
{
    PLISTNODE prev = list->tail;
    list->tail = mknode(sym);
    list->tail->prev = prev;
    if (prev) {
        prev->next = list->tail;
    } else {					/* no previous head */
        list->head = list->tail;
    }
    list->size++;
}

/* free a list */
void listfree(PLIST list)
{
    PLISTNODE N = list->head;
    while (N != NULL) {
        PLISTNODE next = N->next;
        symfree(N->sym);		/* free symbol */
        N = next;
    }
    xfree(list);
}

/* make a new node */
PLISTNODE mknode(PSYMBOL sym)
{
    PLISTNODE N = (PLISTNODE) xmalloc(sizeof(ListNode));
    N->sym = symcopy(sym);
    N->next = N->prev = NULL;
    return N;
}

/* copy a list; possibly deeply */
PLIST listcopy(PLIST src)
{
    PLIST dest = listalloc();

    PLISTNODE N = src->head;
    while (N != NULL) {
        PLISTNODE next = N->next;
        listadd_tail(dest, N->sym);
        N = next;
    }

    return dest;
}

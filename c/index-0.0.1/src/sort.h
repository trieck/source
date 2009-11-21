/*
 *
 * SORT.H : radix sort function
 *
 * When sorting long strings, repetitive string comparison dominates the
 * running time.  The radix sort visits each character in a string at most
 * once, this gives algorithm sub-linear complexity in the number of
 * characters processed.
 *
 * This sort uses a three-way radix sort algorithm taken from "Algorithms
 * in C++", third edition, Robert Sedgewick, pg 436, Addison Wesley, 1998.
 *
 * Copyright(c) 2008 Thomas A. Rieck, All Rights Reserved
 */

#ifndef __SORT_H__
#define __SORT_H__

void radixsort(char *a[], int l, int r, int d);

#endif				/* __SORT_H__ */

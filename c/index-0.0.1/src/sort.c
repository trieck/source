/*
 *
 * SORT.C : radix sort function
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

#include "global.h"
#include "sort.h"

void exch(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

/* Three-way radix sort */
void radixsort(char *a[], int l, int r, int d)
{
    int i, j, k, p, q;
    int v;

    if (r <= l)
        return;

    v = a[r][d];
    i = l - 1;
    j = r;
    p = l - 1;
    q = r;

    while (i < j) {
        while (a[++i][d] < v);

        while (v < a[--j][d])
            if (j == l)
                break;

        if (i > j)
            break;

        exch(&a[i], &a[j]);

        if (a[i][d] == v) {
            p++;
            exch(&a[p], &a[i]);
        }

        if (v == a[j][d]) {
            q--;
            exch(&a[j], &a[q]);
        }
    }

    if (p == q) {
        if (v)
            radixsort(a, l, r, d + 1);

        return;
    }

    if (a[i][d] < v)
        i++;

    for (k = l; k <= p; k++, j--)
        exch(&a[k], &a[j]);

    for (k = r; k >= q; k--, i++)
        exch(&a[k], &a[i]);

    radixsort(a, l, j, d);

    if (i == r && a[i][d] == v)
        i++;

    if (v)
        radixsort(a, j + 1, i - 1, d + 1);

    radixsort(a, i, r, d);
}

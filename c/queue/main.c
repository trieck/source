/*
 * MAIN.C : Application entry point
 *
 * Copyright(c) 2002, Thomas A. Rieck, All Rights Reserved
 *
 */

#include <stdio.h>
#include "queue.h"

/*
 * application entry point
 *
 */
int main(int argc, char *argv[])
{
    char *p;

    struct queue *q = qalloc();

    while (argc--) qput(q, *argv++);

    while ((p = qget(q))) printf("%s\n", p);

    qfree(q);

    return 0;
}

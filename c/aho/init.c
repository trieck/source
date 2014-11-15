/**** init.c ****************************************************************/

#include "global.h"

struct entry keywords[] = {
    "div", DIV,
    "mod", MOD,
    0, 0
};

extern int insert(char s[], int tok);

void init(void)	/* loads keywords into symtable */
{
    struct entry *p;
    for (p = keywords; p->token; p++)
        insert(p->lexptr, p->token);
}
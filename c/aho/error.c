/**** error.c ***************************************************************/

#include "global.h"

void error(char *m)	/* generates all error messages */
{
    fprintf(stderr, "line %d: %s\n", lineno, m);
    exit(1);	/* unsuccessful termination */
}
/**** main.c ***************************************************************/

#include "global.h"

extern void init(void);
extern void parse(void);

void main(void)
{
	init();
	parse();
	exit(0);	/* successful termination */
}
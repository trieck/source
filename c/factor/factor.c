
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static void factors(int n);
static void factor(int n);

/* main entry point */
int main(int argc, char *argv[])
{
	int n;

	if (argc < 2) {
		fprintf(stderr, "usage: factor number\n");
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	if (n < 0) {
		fprintf(stderr, "number must be a positive integer.\n");
		exit(EXIT_FAILURE);
	}

	factors(n);

	return 0;
}

/* print out factors */
void factors(int n)
{
	printf("%d: ", n);
	if (n == 1 || n == 2) {
		printf("%d", n);
	} else if (n == 0) {
		;
	} else {
		factor(n);
	}
}

void factor(int n)
{
	int i = 0, j = floor(sqrt(n)), k = 2;

	for ( ; k <= j; k++) {
		if (n % k == 0) {
			factor(k);
			printf(" ");
			factor(n / k);
			i++;
			break;
		}
	}

	if (i == 0) { /* no factors; prime */
		printf("%d", n);
	}
}

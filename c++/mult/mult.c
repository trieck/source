/*
 * 	MULT.C : Multiplication program
 *	
 *	Demonstrate multiplication algorithm
 *	by only allowing the use of shift operations
 *	and addition.  Also, demonstrate how a microprocessor
 *	would multiply without a MULT instruction.  The idea is to apply
 *	a recursive algorithm and show how we can optimize the operation 
 *	if we are multiplying by powers of two.  
 *
 *	We rely on the property that j * m = j << mlog2, if m is a power of two.
 *
 *	Compare this method with successive addition for large multipliers.
 *	It is theorized that for small numbers, successive addition would be
 *	faster, but what is the improvement for larger numbers, if any?
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

static int multiply(int j, int k);
static int gp2l(int N);
static int log2(int N);

/* 
 * main entry point
 */
int main(void)
{
	int j, k, n;
	
	for (;;) {
		printf("Number 1: ");	
		n = scanf("%d", &j);
		if (1 != n)
			break;
			
		printf("Number 2: ");	
		n = scanf("%d", &k);
		if (1 != n)
			break;
					
		n = multiply(j, k);
		printf("%d * %d = %d\n", j, k, n);
	}
			
	return 0;
}

/* 
 * multiply two numbers
 */
int multiply(int j, int k)
{
	int m;
	
	/*
	 * first, find greatest power of 2 less than k
	 */
	m = gp2l(k);	 
	if (-1 == m) 	/* k is a power of 2, so result is j << klog2  */
		return j << log2(k);
	
	return (j << log2(m)) + multiply(j, k - m);
}

/*
 * greatest power of 2 less than N
 */
int gp2l(int N)
{
	int i, j, k;

	for(i = 0; (j = (1 << i)) <= N; i++) {
		if (j == N)
			return -1;	/* N is power of 2 */

		k = j;	/* greatest power of 2 less than N */
	}

	return k;
}

/*
 * determine log2 for powers of two
 * this is the number of shift rights we
 * can do while N > 0
 */
int log2(int N)
{
	int i = 0;
	
	while ((N >>= 1) > 0)
		++i;
		
	return i;
}



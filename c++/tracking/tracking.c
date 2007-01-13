
#include <stdio.h>
#include <stdlib.h>

int encode(int n1, int n2, int n3, int n4);
void decode(int N, char *buf);

void main(void)
{
	char buf[20];
	int i;

	i = encode(2, 18, 17, 11);
	
	decode(i, buf);	
	printf("%s\n", buf);
}

int encode(int n1, int n2, int n3, int n4)
{
	int N;

	N = n1 | (n2 << 8) | (n3 << 16) | (n4 << 24);

	return N;
}

void decode(int N, char *buf)
{
	int n1, n2, n3, n4;

	n1 = N & 0xFF;
	n2 = (N & 0xFF00) >> 8;
	n3 = (N & 0xFF0000) >> 16;
	n4 = (N & 0xFF000000) >> 24;

	sprintf(buf, "%d:%d:%d:%d", n1, n2, n3, n4);
}


loop = 100;

while ( loop ) {
	a = 0;
	b = 1;
	maxfib = 55;

	while ( b <= maxfib ) {
		printf("%f\t", b);
		c = b;
		b = a + b;
		a = c;
	}
	loop = loop - 1;
}

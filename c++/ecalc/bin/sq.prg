func sq()
{
	return pow($1, 2);
}

i = 0;
while ( i < 100000 ) {
	printf("%f\n", sq(i));
	i = i + 1;
}
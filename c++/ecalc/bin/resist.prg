
func sresist()
{
	return $1 + $2;
}

func presist()
{
	return 1 / ( ( 1 / $1 ) + ( 1 / $2 ) );
}

r1 = 1010;
r2 = 500000;

printf("resistors in series (%f, %f) = [%f]\n", r1, r2, sresist(r1, r2));
printf("resistors in parallel (%f, %f) = [%f]\n", r1, r2, presist(r1, r2));

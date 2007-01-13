func q()
{
	if ($1 > 0)
		return $1 + q($1 -1);
	else return 0;
}

printf("%f", q(100));
func min()
{
	if $1 < $2
		return $1;
	else return $2;
}

func max()
{
	if $1 > $2
		return $1;
	else return $2;
}

printf("%f", 
	max(min(9,11), max(-18,-61))
);